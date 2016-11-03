using System;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using System.Threading;

namespace NetworkManagerUnitTest
{
    [TestClass]
    public class NetworkManager
    {
        /// <summary>
        /// Осуществляет проверку инициализации манеджера
        /// </summary>
        [TestMethod]
        public void CreateNetworkManager()
        {
            //Получаем манаджер
            NetworkTools.Manager.INetworkManager manager = NetworkTools.Manager.NativeMethods.CreateNetworkManager();
            Assert.AreNotEqual(manager, null);
        }
        /// <summary>
        /// Осуществляет получение списка сетевых интерфейсов
        /// </summary>
        [TestMethod]
        public void GetNetworksSettings()
        {
            //Получаем манаджер
            NetworkTools.Manager.INetworkManager manager = NetworkTools.Manager.NativeMethods.CreateNetworkManager();
            if (null == manager){
                Assert.Fail("Invalid init manager.");
            }
            
            //получаем список сетевых интерфейсов
            var ethernets = manager.GetNetworkEthernet();
            Assert.AreNotEqual(manager, null);

            foreach (var ethernet in ethernets)
            {
                var index = ethernet.GetIndex();
                var name = ethernet.GetName();
                var description = ethernet.GetDescription();
                var isVpn = ethernet.IsVpn();

                Assert.AreNotEqual(index, 0);
                Assert.AreNotEqual(name.Length, 0);
                Assert.AreNotEqual(description.Length, 0);

                //получаем список свойств сетевого интерфейса
                var interfaceProfiles = ethernet.GetInterfaceProfiles();
                if (null == interfaceProfiles){
                    return;
                }

                foreach (var profiles in interfaceProfiles)
                {
                    var ip = profiles.GetIp();
                    var mask = profiles.GetMask();

                    Assert.AreNotEqual(ip.Length, 0);
                    Assert.AreNotEqual(mask.Length, 0);
                }
            }
        }

        /// <summary>
        /// Осуществляет постановку задачи
        /// </summary>
        [TestMethod]
        public void CheckTaskScan()
        {
            //Получаем манаджер
            NetworkTools.Manager.INetworkManager manager = NetworkTools.Manager.NativeMethods.CreateNetworkManager();
            if (null == manager){
                Assert.Fail("Invalid init manager.");
            }

            //получение списка устройств с arp таблицы системы (arp -a)
            var arpHost = manager.AddTask(NetworkTools.Manager.TypeScan.ArpHost);
            Assert.AreNotEqual(arpHost, NetworkTools.Manager.TypeAddTask.Fail);
            Assert.AreEqual(arpHost, NetworkTools.Manager.TypeAddTask.NoTask);

            // сканирование arp по всем известным сетевых интерфейсов
            var arp = manager.AddTask(NetworkTools.Manager.TypeScan.Arp);
            Assert.AreNotEqual(arp, NetworkTools.Manager.TypeAddTask.Fail);
            Assert.AreNotEqual(arp, NetworkTools.Manager.TypeAddTask.NoTask);

            // сканирование icmp по всем известным сетевых интерфейсов
            var icmp = manager.AddTask(NetworkTools.Manager.TypeScan.Icmp);
            Assert.AreNotEqual(icmp, NetworkTools.Manager.TypeAddTask.Fail);
            Assert.AreNotEqual(icmp, NetworkTools.Manager.TypeAddTask.NoTask);

            // среднее сканирование сети занимает 3 сек
            Thread.Sleep(4000);

            //Обработка результата
            var arpHostResult = manager.IsTask(arpHost);
            Assert.IsTrue(arpHostResult);

            var arpResult = manager.IsTask(arp);
            Assert.IsTrue(arpResult);

            var icmpResult = manager.IsTask(icmp);
            Assert.IsTrue(icmpResult);           
        }

        /// <summary>
        /// Возвращает список найденых устройств
        /// </summary>
        [TestMethod]
        public void GetHostProfileList()
        {
            //Получаем манаджер
            NetworkTools.Manager.INetworkManager manager = NetworkTools.Manager.NativeMethods.CreateNetworkManager();
            if (null == manager){
                Assert.Fail("Invalid init manager.");
            }

            System.TimeSpan.FromSeconds(10);

            //получаем список сетевых интерфейсов
            var ethernets = manager.GetNetworkEthernet();
            Assert.AreNotEqual(manager, null);

            foreach (var ethernet in ethernets)
            {
                //получаем список найденых узлов для заданного сетевого интерфейса
                var hosts = manager.GetHostProfileList(ethernet);
                Assert.AreNotEqual(hosts.Length, 0);

                //Обработка списка устройств
                foreach (var host in hosts)
                {
                    var ip = host.GetIp();
                    var time = host.GetTime();
                    var name = host.GetName();
                    var version = host.GetOSVersion();
                    var status = host.GetProtectionStatus();
                    var timeInstall = host.GetInstallationDate();
                    var protectedLevel = host.GetProtectedLevel();

                    var licenseBDT = host.GetLicenseBDT();
                    var licenseEDT = host.GetLicenseEDT();
                    var licenseValid = host.GetLicenseValid();
                    var licenseExist = host.GetLicenseExist();

                    Assert.AreNotEqual(ip.Length, 0);
                    Assert.AreNotEqual(time, 0);
                    Assert.AreNotEqual(name.Length, 0);
                    Assert.AreNotEqual(version.Length, 0);
                    Assert.AreNotEqual(status, 0);
                    Assert.AreNotEqual(timeInstall, 0);
                    Assert.AreNotEqual(protectedLevel, 0);
                }
            }
        }
    }
}
