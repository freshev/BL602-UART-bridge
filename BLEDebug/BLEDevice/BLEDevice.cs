// add reference to 
// C:\Program Files (x86)\Windows Kits\10\UnionMetadata\Windows.winmd
// C:\Program Files (x86)\Reference Assemblies\Microsoft\Framework\.NETCore\v4.5\System.Runtime.WindowsRuntime.dll

using System;
using System.Collections.Generic;
using Windows.Devices.Enumeration;
using Windows.Devices.Bluetooth;
using Windows.Devices.Bluetooth.GenericAttributeProfile;
using Windows.Storage.Streams;
using System.Threading.Tasks;

namespace BLEDevice {    

    #region CharacteristicProperties 
    public enum CharacteristicProperties {
        None = 0,
        Broadcast = 1,
        Read = 2,
        WriteWithoutResponse = 4,
        Write = 8,
        Notify = 16,
        Indicate = 32,
        AuthenticatedSignedWrites = 64,
        ExtendedProperties = 128,
        ReliableWrites = 256,
        WritableAuxiliaries = 512
    }
    #endregion

    public class BLEDataReceivedEventArgs : EventArgs { public int BytesToRead { get; set; } }

    public class Characteristic {        

        #region vars
        public Guid UUID = Guid.Empty;
        public List<CharacteristicProperties> Properties = new List<CharacteristicProperties>();
        public GattCharacteristic ReadCharacteristic = null;
        public GattCharacteristic WriteCharacteristic = null;
        public GattCharacteristic WriteAsyncCharacteristic = null;
        public GattCharacteristic NotifyCharacteristic = null;
        public GattCharacteristic IndicateCharacteristic = null;
        private GattReadClientCharacteristicConfigurationDescriptorResult currentDescriptorValueNotify = null;
        private GattReadClientCharacteristicConfigurationDescriptorResult currentDescriptorValueIndicate = null;
        private const string ReadExceptionString = "No bytes to read.";
        public event EventHandler<BLEDataReceivedEventArgs> DataReceived;

        public const int MTUSIZE = 23; // for BLE 4.0 // packet Extension works from BLE 4.2 and above
        private const int BUFFERSIZE = 1024 * 4;
        private Queue<byte> readBuffer = new Queue<byte>();
        public int BytesToRead { get { return readBuffer.Count; } }

        private bool canRead = false;
        public bool CanRead { get { return canRead; } }
        private bool canWrite = false;
        public bool CanWrite { get { return canWrite; } }
        private bool canWriteAsync = false;
        public bool CanWriteAsync { get { return canWriteAsync; } }
        private bool canNotify = false;
        public bool CanNotify { get { return canNotify; } }
        private bool canIndicate= false;
        public bool CanIndicate { get { return canIndicate; } }

        public bool Available() { return readBuffer.Count > 0; }
        #endregion

        #region Add Characteristics
        public void AddReadCharacteristic(GattCharacteristic ch) {
            Properties.Add(CharacteristicProperties.Read);
            ReadCharacteristic = ch;
            canRead = true;
        }
        public void AddWriteCharacteristic(GattCharacteristic ch) {
            Properties.Add(CharacteristicProperties.Write);
            WriteCharacteristic = ch;
            canWrite = true;
        }
        public void AddWriteAsyncCharacteristic(GattCharacteristic ch) {
            Properties.Add(CharacteristicProperties.Write);
            WriteAsyncCharacteristic = ch;
            canWriteAsync = true;
        }
        public async Task AddNotifyCharacteristic(GattCharacteristic ch) {
            currentDescriptorValueNotify = await ch.ReadClientCharacteristicConfigurationDescriptorAsync();
            if (currentDescriptorValueNotify.ClientCharacteristicConfigurationDescriptor != GattClientCharacteristicConfigurationDescriptorValue.Notify) {
                await Task.Delay(100);
                GattCommunicationStatus status = await ch.WriteClientCharacteristicConfigurationDescriptorAsync(GattClientCharacteristicConfigurationDescriptorValue.Notify);
                if (status == GattCommunicationStatus.Success) {
                    ch.ValueChanged += Characteristic_ValueChanged;
                    Properties.Add(CharacteristicProperties.Notify);
                    NotifyCharacteristic = ch;
                    canNotify = true;
                }
            }
        }
        public async Task AddIndicateCharacteristic(GattCharacteristic ch) {
            currentDescriptorValueIndicate = await ch.ReadClientCharacteristicConfigurationDescriptorAsync();
            if (currentDescriptorValueIndicate.ClientCharacteristicConfigurationDescriptor != GattClientCharacteristicConfigurationDescriptorValue.Indicate) {
                await Task.Delay(100);
                GattCommunicationStatus status = await ch.WriteClientCharacteristicConfigurationDescriptorAsync(GattClientCharacteristicConfigurationDescriptorValue.Indicate);
                if (status == GattCommunicationStatus.Success) {
                    ch.ValueChanged += Characteristic_ValueChanged;
                    Properties.Add(CharacteristicProperties.Indicate);
                    IndicateCharacteristic = ch;
                    canIndicate = true;
                }
            }
            
        }
        #endregion

        #region Characteristic_ValueChanged
        public void Characteristic_ValueChanged(GattCharacteristic sender, GattValueChangedEventArgs args) {
            var reader = DataReader.FromBuffer(args.CharacteristicValue);
            while(reader.UnconsumedBufferLength > 0) {
                byte[] input = new byte[reader.UnconsumedBufferLength];
                reader.ReadBytes(input);
                if (input.Length + readBuffer.Count < BUFFERSIZE) {
                    foreach (byte b in input) readBuffer.Enqueue(b);
                } else {
                    // drop
                }
            }
            BLEDataReceivedEventArgs args2 = new BLEDataReceivedEventArgs();
            args2.BytesToRead = readBuffer.Count;
            if (readBuffer.Count > 0) OnDataRecieved(args2);
        }
        protected void OnDataRecieved(BLEDataReceivedEventArgs e) { if (DataReceived != null) DataReceived(this, e); }
        #endregion

        #region Read
        public int Read(byte[] b, int offset, int count) {
            int len = Math.Min(b.Length, readBuffer.Count);
            for (int i = 0; i < len; i++) b[i] = readBuffer.Dequeue();
            return len;
        }

        public byte[] ReadBytes(int count) {
            if (readBuffer.Count > 0) {
                byte[] b = new byte[Math.Min(readBuffer.Count, count)];
                for (int i = 0; i < b.Length; i++) b[i] = readBuffer.Dequeue();
                return b;
            } else throw new Exception(ReadExceptionString);
        }
        public byte ReadByte() {
            if (readBuffer.Count > 0) {
                return readBuffer.Dequeue();
            }
            throw new Exception(ReadExceptionString);
        }
        public short ReadInt16(int count) {
            if (readBuffer.Count >= 2) {
                byte b1 = readBuffer.Dequeue();
                byte b2 = readBuffer.Dequeue();
                return (short)((b1 << 8) + b2);
            }
            throw new Exception(ReadExceptionString);
        }
        public ushort ReadUInt16(int count) {
            if (readBuffer.Count >= 2) {
                byte b1 = readBuffer.Dequeue();
                byte b2 = readBuffer.Dequeue();
                return (ushort)((b1 << 8) + b2);
            }
            throw new Exception(ReadExceptionString);
        }
        public int ReadInt32(int count) {
            if (readBuffer.Count >= 4) {
                byte b1 = readBuffer.Dequeue();
                byte b2 = readBuffer.Dequeue();
                byte b3 = readBuffer.Dequeue();
                byte b4 = readBuffer.Dequeue();
                return (int)((b1 << 24) + (b2 << 16) + (b3 << 8) + b4);
            }
            throw new Exception(ReadExceptionString);
        }
        public uint ReadUInt32(int count) {
            if (readBuffer.Count >= 4) {
                byte b1 = readBuffer.Dequeue();
                byte b2 = readBuffer.Dequeue();
                byte b3 = readBuffer.Dequeue();
                byte b4 = readBuffer.Dequeue();
                return (uint)((b1 << 24) + (b2 << 16) + (b3 << 8) + b4);
            }
            throw new Exception(ReadExceptionString);
        }
        #endregion

        #region Write
        private async Task<bool> WriteSync(byte[] bytes) {
            int bytesToWrite = bytes.Length;
            int counter = 0;
            bool result = true;
            while (bytesToWrite > 0) {
                int len = Math.Min(MTUSIZE, bytesToWrite);
                byte[] buffer = new byte[len];
                Array.Copy(bytes, counter, buffer, 0, len);
                DataWriter writer = new DataWriter();
                writer.WriteBytes(buffer);
                GattWriteResult gattResult = await WriteCharacteristic.WriteValueWithResultAsync(writer.DetachBuffer());
                result &= (gattResult.Status == GattCommunicationStatus.Success);
                bytesToWrite -= len;
                counter += len;
            }
            return result;
        }
        private async Task<bool> WriteAsync(byte[] bytes) {
            int bytesToWrite = bytes.Length;
            int counter = 0;
            GattCommunicationStatus gattResult = GattCommunicationStatus.Success;
            while (bytesToWrite > 0) {
                int len = Math.Min(MTUSIZE, bytesToWrite);
                byte[] buffer = new byte[len];
                Array.Copy(bytes, counter, buffer, 0, len);
                DataWriter writer = new DataWriter();
                writer.WriteBytes(buffer);
                gattResult = gattResult & await WriteAsyncCharacteristic.WriteValueAsync(writer.DetachBuffer());
                bytesToWrite -= len;
                counter += len;
            }
            return (gattResult == GattCommunicationStatus.Success);
        }

        public bool Write(byte[] bytes) {
            try {
                if (CanWrite && WriteCharacteristic != null) {
                    return Task.Run(async() => await WriteSync(bytes)).Result;
                } else if (CanWriteAsync && WriteAsyncCharacteristic != null) {
                    return Task.Run(async () => await WriteAsync(bytes)).Result;
                } else return false;
            } catch (AggregateException ex) { return false;  }
        }
        #endregion

        #region Close
        public async void Close() {
            try {
                if (NotifyCharacteristic != null) {
                    await NotifyCharacteristic.WriteClientCharacteristicConfigurationDescriptorAsync(GattClientCharacteristicConfigurationDescriptorValue.None);
                }
                if (IndicateCharacteristic != null) {
                    await IndicateCharacteristic.WriteClientCharacteristicConfigurationDescriptorAsync(GattClientCharacteristicConfigurationDescriptorValue.None);
                }
            } catch (Exception) { }
            if (currentDescriptorValueNotify != null) currentDescriptorValueNotify = null;
            if (currentDescriptorValueIndicate != null) currentDescriptorValueIndicate = null;
            ReadCharacteristic = null;
            WriteCharacteristic = null;
            WriteAsyncCharacteristic = null;
            NotifyCharacteristic = null;
            IndicateCharacteristic = null;
        }
        #endregion
    }

    public class BLEDevice {

        #region vars        
        private static DeviceWatcher deviceWatcher;
        private static List<BluetoothLEDevice> KnownDevices = new List<BluetoothLEDevice>();
        private static List<DeviceInformation> UnknownDevices = new List<DeviceInformation>();
        private static bool enumerationEnded = false;
        private BluetoothLEDevice device = null;
        private GattDeviceService service = null;
        //private static bool deviceFound = false;
        public List<Characteristic> Characteristics = new List<Characteristic>();
        public string LastError = "";
        #endregion

        #region Properties
        private static string name = "";
        public string Name { get { return name; } set { name = value; } }
        private string serviceUuid = "FFE0";
        public string ServiceUUID { get { return serviceUuid; } set { serviceUuid = value; } }
        private int tickCounter = 0;
        public int TickCounter { get { return tickCounter; } }
        #endregion

        #region Discover
        public static List<string> Discover(int timeout = 10000) {
            try {
                Task.Run(async () => await DiscoverTask(timeout)).Wait();
            } catch (AggregateException ae) {
                throw ae.InnerException ?? ae;
            }
            List<string> list = new List<string>();
            foreach (BluetoothLEDevice dev in KnownDevices) list.Add(dev.Name);
            return list;
        }

        private static async Task<List<BluetoothLEDevice>> DiscoverTask(int timeout = 10000) {
            KnownDevices.Clear();
            UnknownDevices.Clear();
            StartWatcher();
            enumerationEnded = false;
            int count = 0;
            while (!enumerationEnded && count < 100) {
                await Task.Delay(timeout / 100);
                count++;
            }
            enumerationEnded = true;
            StopWatcher();
            return KnownDevices;
        }
        #endregion

        #region Open
        public bool Open() {
            LastError = "";
            return Task.Run(async () => await OpenInternal()).Result;
        }

        private async Task<bool> OpenInternal() {
            if ("".Equals(name)) throw new Exception("Name should be defined first.");
            enumerationEnded = false;
            KnownDevices.Clear();
            UnknownDevices.Clear();
            StartWatcher();
            string targetDeviceId = null;
            while (!enumerationEnded) {
                var known = UnknownDevices.Find(di => di.Name == name);
                if (known == null)
                    known = KnownDevices.Find(bd => bd.Name == name)?.DeviceInformation;

                if (known != null) {
                    targetDeviceId = known.Id;
                    enumerationEnded = true;
                    break;
                }
                await Task.Delay(100);
            }
            StopWatcher();
            if (!string.IsNullOrEmpty(targetDeviceId)) {
                device = await BluetoothLEDevice.FromIdAsync(targetDeviceId);
                if (device != null) {
                    try {
                        GattDeviceServicesResult result = await device.GetGattServicesAsync(BluetoothCacheMode.Uncached);
                        if (result.Status == GattCommunicationStatus.Success) {
                            IReadOnlyList<GattDeviceService> services = result.Services;

                            string serviceId = serviceUuid.PadLeft(8, '0').ToLower() + "-";
                            foreach (GattDeviceService tService in services) {
                                if (!tService.Uuid.ToString().ToLower().StartsWith(serviceId)) {
                                    continue;
                                }
                                service = tService;
                                await Task.Delay(100);
                                GattCharacteristicsResult characteristicsResult = await service.GetCharacteristicsAsync();
                                if (characteristicsResult.Status == GattCommunicationStatus.Success) {
                                    var characteristics = characteristicsResult.Characteristics;
                                    foreach (GattCharacteristic characteristic in characteristics) {
                                        Characteristic ch = new Characteristic();
                                        ch.UUID = characteristic.Uuid;
                                        GattCharacteristicProperties properties = characteristic.CharacteristicProperties;

                                        if (properties.HasFlag(GattCharacteristicProperties.Notify)) await ch.AddNotifyCharacteristic(characteristic);
                                        if (properties.HasFlag(GattCharacteristicProperties.Indicate)) await ch.AddIndicateCharacteristic(characteristic);
                                        if (properties.HasFlag(GattCharacteristicProperties.Read)) ch.AddReadCharacteristic(characteristic);
                                        if (properties.HasFlag(GattCharacteristicProperties.Write)) ch.AddWriteCharacteristic(characteristic);
                                        if (properties.HasFlag(GattCharacteristicProperties.WriteWithoutResponse)) ch.AddWriteAsyncCharacteristic(characteristic);
                                        Characteristics.Add(ch);
                                    }
                                } else {
                                    LastError = "Get Characteristics for device " + name + " failed.";
                                }
                            }
                            enumerationEnded = true;

                            if (service != null) {
                                return true;
                            } else {
                                LastError = "Device " + name + " has not service with UUID starts with \"" + serviceId + "\"";
                            }
                        } else {
                            LastError = "Device " + name + " unreachable or paired with another server.";
                        }
                    } catch (Exception ex) {
                        LastError = ex.Message;
                    }
                } else LastError = "Failed to create Device.";
            } else LastError = "Device not found.";
            return false;
        }
        #endregion

        #region Reconnect
        public bool Reconnect() {
            return Task.Run(async () => await ReconnectInternal()).Result;
        }
        public async Task<bool> ReconnectInternal() {
            bool result = true;
            if (device != null) {
                result &= await CloseInternal();
                result &= await OpenInternal();    
            }
            return result;
        }
        #endregion

        #region Close
        public void Close() {
            Task.Run(async () => await CloseInternal()).Wait();
        }
        private async Task<bool> CloseInternal() {
            if (device != null) {
                foreach (Characteristic ch in Characteristics) ch.Close();                    
                if (service != null) {
                    service.Dispose();
                    service = null;
                }
                device.Dispose();
                device = null;
                await Task.Delay(100);
            }
            return true;
        }
        #endregion

        #region StartWatcher
        private static void StartWatcher() {
            // Additional properties we would like about the device.
            // Property strings are documented here https://msdn.microsoft.com/en-us/library/windows/desktop/ff521659(v=vs.85).aspx
            string[] requestedProperties = { "System.Devices.Aep.DeviceAddress", "System.Devices.Aep.IsConnected", "System.Devices.Aep.Bluetooth.Le.IsConnectable" };
            // BT_Code: Example showing paired and non-paired in a single query.
            string aqsAllBluetoothLEDevices = "(System.Devices.Aep.ProtocolId:=\"{bb7bb05e-5972-42b5-94fc-76eaa7084d49}\")";

            deviceWatcher = DeviceInformation.CreateWatcher(aqsAllBluetoothLEDevices, requestedProperties, DeviceInformationKind.AssociationEndpoint);
            //var trigger = deviceWatcher.GetBackgroundTrigger(new DeviceWatcherEventKind[] { DeviceWatcherEventKind.Add});            
            deviceWatcher.Added += DeviceWatcher_Added;
            deviceWatcher.Updated += DeviceWatcher_Updated;
            deviceWatcher.Removed += DeviceWatcher_Removed;
            deviceWatcher.EnumerationCompleted += DeviceWatcher_EnumerationCompleted;
            deviceWatcher.Stopped += DeviceWatcher_Stopped;
            deviceWatcher.Start();
        }
        #endregion 

        #region StopWatcher
        private static void StopWatcher() {
            if (deviceWatcher != null) {
                deviceWatcher.Added -= DeviceWatcher_Added;
                deviceWatcher.Updated -= DeviceWatcher_Updated;
                deviceWatcher.Removed -= DeviceWatcher_Removed;
                deviceWatcher.EnumerationCompleted -= DeviceWatcher_EnumerationCompleted;
                deviceWatcher.Stopped -= DeviceWatcher_Stopped;

                deviceWatcher.Stop();
                deviceWatcher = null;
            }
        }
        #endregion

        #region FindDevice
        private static BluetoothLEDevice FindBluetoothLEDevice(string id) {
            foreach (BluetoothLEDevice bleDeviceDisplay in KnownDevices) if (bleDeviceDisplay.DeviceId == id) return bleDeviceDisplay;
            return null;
        }
        private static DeviceInformation FindUnknownDevices(string id) {
            foreach (DeviceInformation bleDeviceInfo in UnknownDevices) if (bleDeviceInfo.Id == id) return bleDeviceInfo;
            return null;
        }
        #endregion

        #region Watcher Events
        private static async void DeviceWatcher_Added(DeviceWatcher sender, DeviceInformation deviceInfo) {
            if (sender == deviceWatcher) {
                // Make sure device isn't already present in the list.
                if (FindBluetoothLEDevice(deviceInfo.Id) == null) {
                    if (deviceInfo.Name != string.Empty) {
                        BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromIdAsync(deviceInfo.Id);
                        KnownDevices.Add(bluetoothLeDevice);
                    } else {
                        UnknownDevices.Add(deviceInfo);
                    }
                }
            }
        }

        private static async void DeviceWatcher_Updated(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate) {
            if (sender == deviceWatcher) {
                BluetoothLEDevice bleDevice = FindBluetoothLEDevice(deviceInfoUpdate.Id);
                if (bleDevice != null) {                    
                    return;
                }

                DeviceInformation deviceInfo = FindUnknownDevices(deviceInfoUpdate.Id);
                if (deviceInfo != null) {
                    deviceInfo.Update(deviceInfoUpdate);
                    // If device has been updated with a friendly name it's no longer unknown.
                    if (deviceInfo.Name != string.Empty) {
                        BluetoothLEDevice bluetoothLeDevice = await BluetoothLEDevice.FromIdAsync(deviceInfo.Id);
                        KnownDevices.Add(bluetoothLeDevice);
                        UnknownDevices.Remove(deviceInfo);
                    }
                }
            }
        }

        private static void DeviceWatcher_Removed(DeviceWatcher sender, DeviceInformationUpdate deviceInfoUpdate) {
            if (sender == deviceWatcher) {
                // Find the corresponding DeviceInformation in the collection and remove it.
                BluetoothLEDevice bleDevice = FindBluetoothLEDevice(deviceInfoUpdate.Id);
                if (bleDevice != null) {
                    KnownDevices.Remove(bleDevice);
                }

                DeviceInformation deviceInfo = FindUnknownDevices(deviceInfoUpdate.Id);
                if (deviceInfo != null) {
                    UnknownDevices.Remove(deviceInfo);
                }
            }
        }

        private static void DeviceWatcher_EnumerationCompleted(DeviceWatcher sender, object e) {
            enumerationEnded = true;
        }

        private static void DeviceWatcher_Stopped(DeviceWatcher sender, object e) {
        }
        #endregion

    }
}
