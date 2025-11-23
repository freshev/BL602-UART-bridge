#include "hsf.h"
#include "websocket/private-libwebsockets.h"

#ifndef LWIP_HAVE_POLL
static int lws_poll ( struct libwebsocket_pollfd * fds, unsigned int nfds, int timeout)
{
	int ret, i, max_fd=0;
	fd_set readset, writeset;
	struct timeval tv;
	struct libwebsocket_pollfd *fd = fds;

	tv.tv_sec = timeout/1000;
	tv.tv_usec = timeout%1000 * 1000;
	FD_ZERO(&readset);
	FD_ZERO(&writeset);

	for(i=1;i<nfds+1;i++)
	{
		if(fd->events & POLLIN)
		{
			FD_SET(fd->fd, &readset);
		}

		if(fd->events & POLLOUT){
			FD_SET(fd->fd, &writeset);
		}
		if(fd->fd > max_fd)
			max_fd=fd->fd;
		fd = fd+1;
	}
	ret=select(max_fd+1, &readset, &writeset, 0, &tv);
	fd = fds;
	if(ret == 0) //time out
		;
	else if(ret < 0){
		ret = -1;
	}
	else{
		for(i=1;i<nfds+1;i++)
		{
			if(FD_ISSET(fd->fd, &readset))
				fd->revents |= POLLIN;
			if(FD_ISSET(fd->fd, &writeset))
				fd->revents |= POLLOUT;
			fd = fd + 1;
		}
	}

	return ret;
}
#else
static int lws_poll ( struct libwebsocket_pollfd * fds, unsigned int nfds, int timeout)
{
	return lwip_poll((struct pollfd *)fds, (nfds_t)nfds, timeout);
}
#endif

unsigned long long time_in_microseconds(void)
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000000) + tv.tv_usec;
}

LWS_VISIBLE int libwebsockets_get_random(struct libwebsocket_context *context,
							     void *buf, int len)
{
	int n;
	char *p = (char *)buf;

	for (n = 0; n < len; n++)
		p[n] = (unsigned char)rand();

	return n;

}

LWS_VISIBLE int lws_send_pipe_choked(struct libwebsocket *wsi)
{
	struct libwebsocket_pollfd fds;

	/* treat the fact we got a truncated send pending as if we're choked */
	if (wsi->truncated_send_len)
		return 1;

	fds.fd = wsi->sock;
	fds.events = POLLOUT;
	fds.revents = 0;

	if (lws_poll(&fds, 1, 0) != 1)
		return 1;

	if ((fds.revents & POLLOUT) == 0)
		return 1;

	/* okay to send another packet without blocking */

	return 0;
}

LWS_VISIBLE int
lws_poll_listen_fd(struct libwebsocket_pollfd *fd)
{
	return lws_poll(fd, 1, 0);
}

/**
 * libwebsocket_cancel_service() - Cancel servicing of pending websocket activity
 * @context:	Websocket context
 *
 *	This function let a call to libwebsocket_service() waiting for a timeout
 *	immediately return.
 */
LWS_VISIBLE void
libwebsocket_cancel_service(struct libwebsocket_context *context)
{
#ifdef PORTING_FREERTOS
	char buf = 0;

	if (write(context->dummy_pipe_fds[1], &buf, sizeof(buf)) != 1)
		lwsl_err("Cannot write to dummy pipe");
#endif
}

LWS_VISIBLE int
lws_plat_service(struct libwebsocket_context *context, int timeout_ms)
{
	int n;
	int m;
	//char buf;

	/* stay dead once we are dead */

	if (!context)
		return 1;

	//lws_libev_run(context);

	context->service_tid = context->protocols[0].callback(context, NULL,
				     LWS_CALLBACK_GET_THREAD_ID, NULL, NULL, 0);

	n = lws_poll(context->fds, context->fds_count, timeout_ms);
	context->service_tid = 0;

	if (n == 0) /* poll timeout */ {
		libwebsocket_service_fd(context, NULL);
		return 0;
	}

	if (n < 0) {
		if (LWS_ERRNO != LWS_EINTR)
			return -1;
		return 0;
	}

	/* any socket with events to service? */

	for (n = 0; n < context->fds_count; n++) {
		if (!context->fds[n].revents)
			continue;
#ifdef PORTING_FREERTOS
		if (context->fds[n].fd == context->dummy_pipe_fds[0]) {
			if (read(context->fds[n].fd, &buf, 1) != 1)
				lwsl_err("Cannot read from dummy pipe.");
			continue;
		}
#endif
		m = libwebsocket_service_fd(context, &context->fds[n]);
		if (m < 0)
			return -1;
		/* if something closed, retry this slot */
		if (m)
			n--;
	}

	return 0;
}

LWS_VISIBLE int
lws_plat_set_socket_options(struct libwebsocket_context *context, int fd)
{
	int optval = 1;
	socklen_t optlen = sizeof(optval);

	if (context->ka_time) {
		/* enable keepalive on this socket */
		optval = 1;
		if (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE,
					     (const void *)&optval, optlen) < 0)
			return 1;

		/* set the keepalive conditions we want on it too */
		optval = context->ka_time;
		if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPIDLE,
					     (const void *)&optval, optlen) < 0)
			return 1;

		optval = context->ka_interval;
		if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPINTVL,
					     (const void *)&optval, optlen) < 0)
			return 1;

		optval = context->ka_probes;
		if (setsockopt(fd, IPPROTO_TCP, TCP_KEEPCNT,
					     (const void *)&optval, optlen) < 0)
			return 1;
	}

	/* Disable Nagle */
	optval = 1;
	setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, (const void *)&optval, optlen);

	/* We are nonblocking... */
	//fcntl(fd, F_SETFL, O_NONBLOCK);

	return 0;
}

LWS_VISIBLE void
lws_plat_drop_app_privileges(struct lws_context_creation_info *info)
{
}

LWS_VISIBLE int
lws_plat_init_fd_tables(struct libwebsocket_context *context)
{
	//if (pipe(context->dummy_pipe_fds)) {
	//	lwsl_err("Unable to create pipe\n");
	//	return 1;
	//}
#ifdef PORTING_FREERTOS
	/* use the read end of pipe as first item */
	context->fds[0].fd = context->dummy_pipe_fds[0];
	context->fds[0].events = LWS_POLLIN;
	context->fds[0].revents = 0;
	context->fds_count = 1;

	context->fd_random = open(SYSTEM_RANDOM_FILEPATH, O_RDONLY);
	if (context->fd_random < 0) {
		lwsl_err("Unable to open random device %s %d\n",
				    SYSTEM_RANDOM_FILEPATH, context->fd_random);
		return 1;
	}
#else
	context->fds_count = 0;
#endif
	return 0;
}

LWS_VISIBLE int
lws_plat_context_early_init(void)
{
	return 0;
}

LWS_VISIBLE void
lws_plat_context_early_destroy(struct libwebsocket_context *context)
{
}

LWS_VISIBLE void
lws_plat_context_late_destroy(struct libwebsocket_context *context)
{
#ifdef PORTING_FREERTOS
	close(context->dummy_pipe_fds[0]);
	close(context->dummy_pipe_fds[1]);
#endif
}

LWS_VISIBLE void
lws_plat_insert_socket_into_fds(struct libwebsocket_context *context,
						       struct libwebsocket *wsi)
{
	//lws_libev_io(context, wsi, LWS_EV_START | LWS_EV_READ);
	context->fds[context->fds_count++].revents = 0;
}

LWS_VISIBLE void
lws_plat_delete_socket_from_fds(struct libwebsocket_context *context,
						struct libwebsocket *wsi, int m)
{
}

LWS_VISIBLE void
lws_plat_service_periodic(struct libwebsocket_context *context)
{
}

LWS_VISIBLE int
lws_plat_change_pollfd(struct libwebsocket_context *context,
		      struct libwebsocket *wsi, struct libwebsocket_pollfd *pfd)
{
	return 0;
}

#ifdef LWS_USE_IPV6
LWS_VISIBLE const char *
lws_plat_inet_ntop(int af, const void *src, char *dst, int cnt)
{
	return inet_ntop(af, src, dst, cnt);
}
#endif
