using System;
using System.Runtime.InteropServices;
using System.Runtime.CompilerServices;

namespace NetworkTools.Manager
{
    /// <summary>
    /// Тип сканирования
    /// </summary>
    enum TypeScan
    {
	    /// Arp сканирование
	    Arp,
	    /// Анализ arp таблицы хоста
	    ArpHost,
	    /// Icmp сканирование
	    Icmp
    };
    /// <summary>
    /// Уровень защиты
    /// </summary>
    enum TypeProtected
    { 
        Unknown,
	    Normal,
        TrustedVendors,
        Strict
    }


    /// <summary>
    /// Результат обработки при постановки задачи
    /// </summary>
    static class TypeAddTask
    {
        /// <summary>
        /// Не удалось выставить задачу
        /// </summary>
        public const int Fail = -1;
        /// <summary>
        /// На выполнение сканирование не требуется постановка сканирования, так как задача выполняется синхронно
        /// </summary>
        public const int NoTask = 0;
    }

    /// <summary>
    /// Описание менеджера осуществляющий работу с сетью
    /// </summary>
    static class NativeMethods
    {

        [DllImport("networktools", CallingConvention = CallingConvention.StdCall)]
        [return: MarshalAs(UnmanagedType.Interface)]
        public static extern INetworkManager CreateNetworkManager();
    }

    /// <summary>
    /// Описание узла
    /// </summary>
    [ComImport]
    [Guid("864DFD92-00C7-43E4-8856-CD3490769CDA")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IHostProfile
    {
        /// <summary>
        /// Возвращает Ip адрес
        /// </summary>
        /// <returns>Ip адрес</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetIp();
        /// <summary>
        /// Возвращает время ответа
        /// </summary>
        /// <returns>Время ответа</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetTime();
        /// <summary>
        /// Возвращает имя узла
        /// </summary>
        /// <returns>Имя узла</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetName();
        /// <summary>
        /// Возвращает версию OS
        /// </summary>
        /// <returns>Имя узла</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetOSVersion();
        /// <summary>
        /// Возвращает статус
        /// </summary>
        /// <returns>Cтатус</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetProtectionStatus();
        /// <summary>
        /// Возвращает время установки приложения
        /// </summary>
        /// <returns>Время установки приложения</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetInstallationDate();
        /// <summary>
        /// Возвращает уровень защиты Normal/Trusted Vendors/Strict
        /// </summary>
        /// <returns>Уровень защиты</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        TypeProtected GetProtectedLevel();
        /// <summary>
        /// Возвращает занчение поля "Exits"
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetLicenseExist();
        /// <summary>
        /// ISO строка времени начала действия
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetLicenseBDT();
        /// <summary>
        /// ISO строка времени окончания действия
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetLicenseEDT();
        /// <summary>
        /// Возвращает действительна лицензия "1" - да, "0" - нет.
        /// </summary>
        /// <returns></returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetLicenseValid();
    }

    /// <summary>
    /// Описание сетевых настроек
    /// </summary>
    [ComImport]
    [Guid("6F4EBF8F-A620-4CEA-8A88-2A168563A9E0")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface InterfaceProfiles
    {
        /// <summary>
        /// Возвращает Ip адрес
        /// </summary>
        /// <returns>Ip адрес</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetIp();
        
        /// <summary>
        /// Возвращает Маску
        /// </summary>
        /// <returns>Возвращает Маску</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetMask();
    }

    /// <summary>
    /// Описание Cетевого интерфейса
    /// </summary>
    [ComImport]
    [Guid("2B3F116C-2717-4A29-8C5E-50F2566BFFC7")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface IEthernetProfile
    {
        /// <summary>
        /// Возвращает индекс сетевого интерфейса
        /// </summary>
        /// <returns>Индекс сетевого интерфейса</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int GetIndex();

        /// <summary>
        /// Возвращает true если определен признак VPN
        /// </summary>
        /// <returns>озвращает true если определен признак VPN</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        bool IsVpn();

        /// <summary>
        /// Возвращает имя интерфейса
        /// </summary>
        /// <returns>Имя интерфейса</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetName();

        /// <summary>
        /// Возвращает описание интерфейса
        /// </summary>
        /// <returns>Описание интерфейса</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.BStr)]
        string GetDescription();
        /// <summary>
        /// Возвращает список сетевых настроек
        /// </summary>
        /// <returns>Список сетевых настроек</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_UNKNOWN)]
        InterfaceProfiles[] GetInterfaceProfiles();
    }

    [ComImport]
    [Guid("D1C66136-AB61-4F6C-8984-50B128750CD1")]
    [InterfaceType(ComInterfaceType.InterfaceIsIUnknown)]
    internal interface INetworkManager
    {
        /// <summary>
        /// Врзвращает список сетевых интерфейсов
        /// </summary>
        /// <returns>Список сетевых интерфейсов</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_UNKNOWN)]
        IEthernetProfile[] GetNetworkEthernet();

        /// <summary>
        /// Возвращает список сетевых узлов для заданного интерфейса
        /// </summary>
        /// <param name="ethernetProfile">сетевой интерфейс</param>
        /// <returns>Список сетевых узлов</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        [return: MarshalAs(UnmanagedType.SafeArray, SafeArraySubType = VarEnum.VT_UNKNOWN)]
        IHostProfile[] GetHostProfileList([In, MarshalAs(UnmanagedType.Interface)] IEthernetProfile ethernetProfile );

        /// <summary>
        /// Ставит задачу в очередь
        /// </summary>
        /// <param name="typeScan">Тип сканирования</param>
        /// <returns>Возвращает id задачи</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        int AddTask([In, MarshalAs(UnmanagedType.I4)] TypeScan typeScan);

        /// <summary>
        /// Проверка завершение выполнения поствленной задачи
        /// </summary>
        /// <param name="idTask">задача</param>
        /// <returns>Возвращает true если задача заврешена</returns>
        [MethodImpl(MethodImplOptions.InternalCall, MethodCodeType = MethodCodeType.Runtime)]
        [PreserveSig]
        bool IsTask([In, MarshalAs(UnmanagedType.I4)] int idTask);
    }
}

