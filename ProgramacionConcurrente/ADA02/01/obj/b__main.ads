pragma Ada_95;
with System;
package ada_main is
   pragma Warnings (Off);

   gnat_argc : Integer;
   gnat_argv : System.Address;
   gnat_envp : System.Address;

   pragma Import (C, gnat_argc);
   pragma Import (C, gnat_argv);
   pragma Import (C, gnat_envp);

   gnat_exit_status : Integer;
   pragma Import (C, gnat_exit_status);

   GNAT_Version : constant String :=
                    "GNAT Version: 5.4.0" & ASCII.NUL;
   pragma Export (C, GNAT_Version, "__gnat_version");

   Ada_Main_Program_Name : constant String := "_ada_main" & ASCII.NUL;
   pragma Export (C, Ada_Main_Program_Name, "__gnat_ada_main_program_name");

   procedure adainit;
   pragma Export (C, adainit, "adainit");

   procedure adafinal;
   pragma Export (C, adafinal, "adafinal");

   function main
     (argc : Integer;
      argv : System.Address;
      envp : System.Address)
      return Integer;
   pragma Export (C, main, "main");

   type Version_32 is mod 2 ** 32;
   u00001 : constant Version_32 := 16#0e0cdf33#;
   pragma Export (C, u00001, "mainB");
   u00002 : constant Version_32 := 16#fbff4c67#;
   pragma Export (C, u00002, "system__standard_libraryB");
   u00003 : constant Version_32 := 16#1ec6fd90#;
   pragma Export (C, u00003, "system__standard_libraryS");
   u00004 : constant Version_32 := 16#3ffc8e18#;
   pragma Export (C, u00004, "adaS");
   u00005 : constant Version_32 := 16#fa9a1bab#;
   pragma Export (C, u00005, "ada__real_timeB");
   u00006 : constant Version_32 := 16#2028f6ad#;
   pragma Export (C, u00006, "ada__real_timeS");
   u00007 : constant Version_32 := 16#6033a23f#;
   pragma Export (C, u00007, "interfacesS");
   u00008 : constant Version_32 := 16#1d274481#;
   pragma Export (C, u00008, "systemS");
   u00009 : constant Version_32 := 16#1f99af62#;
   pragma Export (C, u00009, "system__arith_64B");
   u00010 : constant Version_32 := 16#3d59434c#;
   pragma Export (C, u00010, "system__arith_64S");
   u00011 : constant Version_32 := 16#2c143749#;
   pragma Export (C, u00011, "ada__exceptionsB");
   u00012 : constant Version_32 := 16#f4f0cce8#;
   pragma Export (C, u00012, "ada__exceptionsS");
   u00013 : constant Version_32 := 16#a46739c0#;
   pragma Export (C, u00013, "ada__exceptions__last_chance_handlerB");
   u00014 : constant Version_32 := 16#3aac8c92#;
   pragma Export (C, u00014, "ada__exceptions__last_chance_handlerS");
   u00015 : constant Version_32 := 16#a207fefe#;
   pragma Export (C, u00015, "system__soft_linksB");
   u00016 : constant Version_32 := 16#467d9556#;
   pragma Export (C, u00016, "system__soft_linksS");
   u00017 : constant Version_32 := 16#b01dad17#;
   pragma Export (C, u00017, "system__parametersB");
   u00018 : constant Version_32 := 16#630d49fe#;
   pragma Export (C, u00018, "system__parametersS");
   u00019 : constant Version_32 := 16#b19b6653#;
   pragma Export (C, u00019, "system__secondary_stackB");
   u00020 : constant Version_32 := 16#b6468be8#;
   pragma Export (C, u00020, "system__secondary_stackS");
   u00021 : constant Version_32 := 16#39a03df9#;
   pragma Export (C, u00021, "system__storage_elementsB");
   u00022 : constant Version_32 := 16#30e40e85#;
   pragma Export (C, u00022, "system__storage_elementsS");
   u00023 : constant Version_32 := 16#41837d1e#;
   pragma Export (C, u00023, "system__stack_checkingB");
   u00024 : constant Version_32 := 16#93982f69#;
   pragma Export (C, u00024, "system__stack_checkingS");
   u00025 : constant Version_32 := 16#393398c1#;
   pragma Export (C, u00025, "system__exception_tableB");
   u00026 : constant Version_32 := 16#b33e2294#;
   pragma Export (C, u00026, "system__exception_tableS");
   u00027 : constant Version_32 := 16#ce4af020#;
   pragma Export (C, u00027, "system__exceptionsB");
   u00028 : constant Version_32 := 16#75442977#;
   pragma Export (C, u00028, "system__exceptionsS");
   u00029 : constant Version_32 := 16#37d758f1#;
   pragma Export (C, u00029, "system__exceptions__machineS");
   u00030 : constant Version_32 := 16#b895431d#;
   pragma Export (C, u00030, "system__exceptions_debugB");
   u00031 : constant Version_32 := 16#aec55d3f#;
   pragma Export (C, u00031, "system__exceptions_debugS");
   u00032 : constant Version_32 := 16#570325c8#;
   pragma Export (C, u00032, "system__img_intB");
   u00033 : constant Version_32 := 16#1ffca443#;
   pragma Export (C, u00033, "system__img_intS");
   u00034 : constant Version_32 := 16#b98c3e16#;
   pragma Export (C, u00034, "system__tracebackB");
   u00035 : constant Version_32 := 16#831a9d5a#;
   pragma Export (C, u00035, "system__tracebackS");
   u00036 : constant Version_32 := 16#9ed49525#;
   pragma Export (C, u00036, "system__traceback_entriesB");
   u00037 : constant Version_32 := 16#1d7cb2f1#;
   pragma Export (C, u00037, "system__traceback_entriesS");
   u00038 : constant Version_32 := 16#8c33a517#;
   pragma Export (C, u00038, "system__wch_conB");
   u00039 : constant Version_32 := 16#065a6653#;
   pragma Export (C, u00039, "system__wch_conS");
   u00040 : constant Version_32 := 16#9721e840#;
   pragma Export (C, u00040, "system__wch_stwB");
   u00041 : constant Version_32 := 16#2b4b4a52#;
   pragma Export (C, u00041, "system__wch_stwS");
   u00042 : constant Version_32 := 16#92b797cb#;
   pragma Export (C, u00042, "system__wch_cnvB");
   u00043 : constant Version_32 := 16#09eddca0#;
   pragma Export (C, u00043, "system__wch_cnvS");
   u00044 : constant Version_32 := 16#ece6fdb6#;
   pragma Export (C, u00044, "system__wch_jisB");
   u00045 : constant Version_32 := 16#899dc581#;
   pragma Export (C, u00045, "system__wch_jisS");
   u00046 : constant Version_32 := 16#f3a0b2fb#;
   pragma Export (C, u00046, "system__taskingB");
   u00047 : constant Version_32 := 16#a0152c3e#;
   pragma Export (C, u00047, "system__taskingS");
   u00048 : constant Version_32 := 16#176e813d#;
   pragma Export (C, u00048, "system__task_primitivesS");
   u00049 : constant Version_32 := 16#9a3bced2#;
   pragma Export (C, u00049, "system__os_interfaceB");
   u00050 : constant Version_32 := 16#3d00370a#;
   pragma Export (C, u00050, "system__os_interfaceS");
   u00051 : constant Version_32 := 16#769e25e6#;
   pragma Export (C, u00051, "interfaces__cB");
   u00052 : constant Version_32 := 16#4a38bedb#;
   pragma Export (C, u00052, "interfaces__cS");
   u00053 : constant Version_32 := 16#66dc3fcb#;
   pragma Export (C, u00053, "system__linuxS");
   u00054 : constant Version_32 := 16#02d35348#;
   pragma Export (C, u00054, "system__os_constantsS");
   u00055 : constant Version_32 := 16#807fe041#;
   pragma Export (C, u00055, "system__unsigned_typesS");
   u00056 : constant Version_32 := 16#6b5de5f0#;
   pragma Export (C, u00056, "system__task_primitives__operationsB");
   u00057 : constant Version_32 := 16#5a266085#;
   pragma Export (C, u00057, "system__task_primitives__operationsS");
   u00058 : constant Version_32 := 16#fa38f350#;
   pragma Export (C, u00058, "interfaces__c__extensionsS");
   u00059 : constant Version_32 := 16#a87ab9e2#;
   pragma Export (C, u00059, "system__bit_opsB");
   u00060 : constant Version_32 := 16#0765e3a3#;
   pragma Export (C, u00060, "system__bit_opsS");
   u00061 : constant Version_32 := 16#66645a25#;
   pragma Export (C, u00061, "system__interrupt_managementB");
   u00062 : constant Version_32 := 16#e75eca89#;
   pragma Export (C, u00062, "system__interrupt_managementS");
   u00063 : constant Version_32 := 16#f65595cf#;
   pragma Export (C, u00063, "system__multiprocessorsB");
   u00064 : constant Version_32 := 16#258bdbf2#;
   pragma Export (C, u00064, "system__multiprocessorsS");
   u00065 : constant Version_32 := 16#be1316da#;
   pragma Export (C, u00065, "system__os_primitivesB");
   u00066 : constant Version_32 := 16#adf6c8a8#;
   pragma Export (C, u00066, "system__os_primitivesS");
   u00067 : constant Version_32 := 16#664ed994#;
   pragma Export (C, u00067, "system__stack_checking__operationsB");
   u00068 : constant Version_32 := 16#64c2cb2b#;
   pragma Export (C, u00068, "system__stack_checking__operationsS");
   u00069 : constant Version_32 := 16#6db6928f#;
   pragma Export (C, u00069, "system__crtlS");
   u00070 : constant Version_32 := 16#375a3ef7#;
   pragma Export (C, u00070, "system__task_infoB");
   u00071 : constant Version_32 := 16#dffa4746#;
   pragma Export (C, u00071, "system__task_infoS");
   u00072 : constant Version_32 := 16#e737d8df#;
   pragma Export (C, u00072, "system__tasking__debugB");
   u00073 : constant Version_32 := 16#364be463#;
   pragma Export (C, u00073, "system__tasking__debugS");
   u00074 : constant Version_32 := 16#fd83e873#;
   pragma Export (C, u00074, "system__concat_2B");
   u00075 : constant Version_32 := 16#1f879351#;
   pragma Export (C, u00075, "system__concat_2S");
   u00076 : constant Version_32 := 16#2b70b149#;
   pragma Export (C, u00076, "system__concat_3B");
   u00077 : constant Version_32 := 16#16571824#;
   pragma Export (C, u00077, "system__concat_3S");
   u00078 : constant Version_32 := 16#d0432c8d#;
   pragma Export (C, u00078, "system__img_enum_newB");
   u00079 : constant Version_32 := 16#7c6b4241#;
   pragma Export (C, u00079, "system__img_enum_newS");
   u00080 : constant Version_32 := 16#9777733a#;
   pragma Export (C, u00080, "system__img_lliB");
   u00081 : constant Version_32 := 16#0c681150#;
   pragma Export (C, u00081, "system__img_lliS");
   u00082 : constant Version_32 := 16#118e865d#;
   pragma Export (C, u00082, "system__stack_usageB");
   u00083 : constant Version_32 := 16#00bc3311#;
   pragma Export (C, u00083, "system__stack_usageS");
   u00084 : constant Version_32 := 16#d7aac20c#;
   pragma Export (C, u00084, "system__ioB");
   u00085 : constant Version_32 := 16#8365b3ce#;
   pragma Export (C, u00085, "system__ioS");
   u00086 : constant Version_32 := 16#12c8cd7d#;
   pragma Export (C, u00086, "ada__tagsB");
   u00087 : constant Version_32 := 16#ce72c228#;
   pragma Export (C, u00087, "ada__tagsS");
   u00088 : constant Version_32 := 16#c3335bfd#;
   pragma Export (C, u00088, "system__htableB");
   u00089 : constant Version_32 := 16#99e5f76b#;
   pragma Export (C, u00089, "system__htableS");
   u00090 : constant Version_32 := 16#089f5cd0#;
   pragma Export (C, u00090, "system__string_hashB");
   u00091 : constant Version_32 := 16#3bbb9c15#;
   pragma Export (C, u00091, "system__string_hashS");
   u00092 : constant Version_32 := 16#06052bd0#;
   pragma Export (C, u00092, "system__val_lluB");
   u00093 : constant Version_32 := 16#fa8db733#;
   pragma Export (C, u00093, "system__val_lluS");
   u00094 : constant Version_32 := 16#27b600b2#;
   pragma Export (C, u00094, "system__val_utilB");
   u00095 : constant Version_32 := 16#b187f27f#;
   pragma Export (C, u00095, "system__val_utilS");
   u00096 : constant Version_32 := 16#d1060688#;
   pragma Export (C, u00096, "system__case_utilB");
   u00097 : constant Version_32 := 16#392e2d56#;
   pragma Export (C, u00097, "system__case_utilS");
   u00098 : constant Version_32 := 16#c1a106e2#;
   pragma Export (C, u00098, "ada__text_ioB");
   u00099 : constant Version_32 := 16#f372c8ac#;
   pragma Export (C, u00099, "ada__text_ioS");
   u00100 : constant Version_32 := 16#10558b11#;
   pragma Export (C, u00100, "ada__streamsB");
   u00101 : constant Version_32 := 16#2e6701ab#;
   pragma Export (C, u00101, "ada__streamsS");
   u00102 : constant Version_32 := 16#db5c917c#;
   pragma Export (C, u00102, "ada__io_exceptionsS");
   u00103 : constant Version_32 := 16#84a27f0d#;
   pragma Export (C, u00103, "interfaces__c_streamsB");
   u00104 : constant Version_32 := 16#8bb5f2c0#;
   pragma Export (C, u00104, "interfaces__c_streamsS");
   u00105 : constant Version_32 := 16#431faf3c#;
   pragma Export (C, u00105, "system__file_ioB");
   u00106 : constant Version_32 := 16#ba56a5e4#;
   pragma Export (C, u00106, "system__file_ioS");
   u00107 : constant Version_32 := 16#b7ab275c#;
   pragma Export (C, u00107, "ada__finalizationB");
   u00108 : constant Version_32 := 16#19f764ca#;
   pragma Export (C, u00108, "ada__finalizationS");
   u00109 : constant Version_32 := 16#95817ed8#;
   pragma Export (C, u00109, "system__finalization_rootB");
   u00110 : constant Version_32 := 16#52d53711#;
   pragma Export (C, u00110, "system__finalization_rootS");
   u00111 : constant Version_32 := 16#07e6ee66#;
   pragma Export (C, u00111, "system__os_libB");
   u00112 : constant Version_32 := 16#d7b69782#;
   pragma Export (C, u00112, "system__os_libS");
   u00113 : constant Version_32 := 16#1a817b8e#;
   pragma Export (C, u00113, "system__stringsB");
   u00114 : constant Version_32 := 16#639855e7#;
   pragma Export (C, u00114, "system__stringsS");
   u00115 : constant Version_32 := 16#e0b8de29#;
   pragma Export (C, u00115, "system__file_control_blockS");
   u00116 : constant Version_32 := 16#ffdce1e2#;
   pragma Export (C, u00116, "system__tasking__rendezvousB");
   u00117 : constant Version_32 := 16#71fce298#;
   pragma Export (C, u00117, "system__tasking__rendezvousS");
   u00118 : constant Version_32 := 16#100eaf58#;
   pragma Export (C, u00118, "system__restrictionsB");
   u00119 : constant Version_32 := 16#51ab495f#;
   pragma Export (C, u00119, "system__restrictionsS");
   u00120 : constant Version_32 := 16#b1c8176f#;
   pragma Export (C, u00120, "system__tasking__entry_callsB");
   u00121 : constant Version_32 := 16#e903595c#;
   pragma Export (C, u00121, "system__tasking__entry_callsS");
   u00122 : constant Version_32 := 16#de78d4d4#;
   pragma Export (C, u00122, "system__tasking__initializationB");
   u00123 : constant Version_32 := 16#d9930fa8#;
   pragma Export (C, u00123, "system__tasking__initializationS");
   u00124 : constant Version_32 := 16#c3044b40#;
   pragma Export (C, u00124, "system__soft_links__taskingB");
   u00125 : constant Version_32 := 16#e47ef8be#;
   pragma Export (C, u00125, "system__soft_links__taskingS");
   u00126 : constant Version_32 := 16#17d21067#;
   pragma Export (C, u00126, "ada__exceptions__is_null_occurrenceB");
   u00127 : constant Version_32 := 16#9a9e8fd3#;
   pragma Export (C, u00127, "ada__exceptions__is_null_occurrenceS");
   u00128 : constant Version_32 := 16#1b84470b#;
   pragma Export (C, u00128, "system__tasking__task_attributesB");
   u00129 : constant Version_32 := 16#952bcf5e#;
   pragma Export (C, u00129, "system__tasking__task_attributesS");
   u00130 : constant Version_32 := 16#9a283644#;
   pragma Export (C, u00130, "system__tasking__protected_objectsB");
   u00131 : constant Version_32 := 16#63b50013#;
   pragma Export (C, u00131, "system__tasking__protected_objectsS");
   u00132 : constant Version_32 := 16#ee80728a#;
   pragma Export (C, u00132, "system__tracesB");
   u00133 : constant Version_32 := 16#ef3a2c2b#;
   pragma Export (C, u00133, "system__tracesS");
   u00134 : constant Version_32 := 16#fdb2ef41#;
   pragma Export (C, u00134, "system__tasking__protected_objects__entriesB");
   u00135 : constant Version_32 := 16#7671a6ef#;
   pragma Export (C, u00135, "system__tasking__protected_objects__entriesS");
   u00136 : constant Version_32 := 16#ac92c59a#;
   pragma Export (C, u00136, "system__tasking__protected_objects__operationsB");
   u00137 : constant Version_32 := 16#eb67f071#;
   pragma Export (C, u00137, "system__tasking__protected_objects__operationsS");
   u00138 : constant Version_32 := 16#57df25b5#;
   pragma Export (C, u00138, "system__tasking__queuingB");
   u00139 : constant Version_32 := 16#3117b7f1#;
   pragma Export (C, u00139, "system__tasking__queuingS");
   u00140 : constant Version_32 := 16#05f5974e#;
   pragma Export (C, u00140, "system__tasking__utilitiesB");
   u00141 : constant Version_32 := 16#65f77ff8#;
   pragma Export (C, u00141, "system__tasking__utilitiesS");
   u00142 : constant Version_32 := 16#bd6fc52e#;
   pragma Export (C, u00142, "system__traces__taskingB");
   u00143 : constant Version_32 := 16#3fb127e5#;
   pragma Export (C, u00143, "system__traces__taskingS");
   u00144 : constant Version_32 := 16#9a56d494#;
   pragma Export (C, u00144, "system__tasking__stagesB");
   u00145 : constant Version_32 := 16#14057fdd#;
   pragma Export (C, u00145, "system__tasking__stagesS");
   u00146 : constant Version_32 := 16#57a37a42#;
   pragma Export (C, u00146, "system__address_imageB");
   u00147 : constant Version_32 := 16#bccbd9bb#;
   pragma Export (C, u00147, "system__address_imageS");
   u00148 : constant Version_32 := 16#9d39c675#;
   pragma Export (C, u00148, "system__memoryB");
   u00149 : constant Version_32 := 16#445a22b5#;
   pragma Export (C, u00149, "system__memoryS");
   --  BEGIN ELABORATION ORDER
   --  ada%s
   --  interfaces%s
   --  system%s
   --  system.arith_64%s
   --  system.case_util%s
   --  system.case_util%b
   --  system.htable%s
   --  system.img_enum_new%s
   --  system.img_enum_new%b
   --  system.img_int%s
   --  system.img_int%b
   --  system.img_lli%s
   --  system.img_lli%b
   --  system.io%s
   --  system.io%b
   --  system.multiprocessors%s
   --  system.os_primitives%s
   --  system.os_primitives%b
   --  system.parameters%s
   --  system.parameters%b
   --  system.crtl%s
   --  interfaces.c_streams%s
   --  interfaces.c_streams%b
   --  system.restrictions%s
   --  system.restrictions%b
   --  system.standard_library%s
   --  system.exceptions_debug%s
   --  system.exceptions_debug%b
   --  system.storage_elements%s
   --  system.storage_elements%b
   --  system.stack_checking%s
   --  system.stack_checking%b
   --  system.stack_checking.operations%s
   --  system.stack_usage%s
   --  system.stack_usage%b
   --  system.string_hash%s
   --  system.string_hash%b
   --  system.htable%b
   --  system.strings%s
   --  system.strings%b
   --  system.os_lib%s
   --  system.traceback_entries%s
   --  system.traceback_entries%b
   --  ada.exceptions%s
   --  system.arith_64%b
   --  ada.exceptions.is_null_occurrence%s
   --  ada.exceptions.is_null_occurrence%b
   --  system.soft_links%s
   --  system.stack_checking.operations%b
   --  system.traces%s
   --  system.traces%b
   --  system.unsigned_types%s
   --  system.val_llu%s
   --  system.val_util%s
   --  system.val_util%b
   --  system.val_llu%b
   --  system.wch_con%s
   --  system.wch_con%b
   --  system.wch_cnv%s
   --  system.wch_jis%s
   --  system.wch_jis%b
   --  system.wch_cnv%b
   --  system.wch_stw%s
   --  system.wch_stw%b
   --  ada.exceptions.last_chance_handler%s
   --  ada.exceptions.last_chance_handler%b
   --  system.address_image%s
   --  system.bit_ops%s
   --  system.bit_ops%b
   --  system.concat_2%s
   --  system.concat_2%b
   --  system.concat_3%s
   --  system.concat_3%b
   --  system.exception_table%s
   --  system.exception_table%b
   --  ada.io_exceptions%s
   --  ada.tags%s
   --  ada.streams%s
   --  ada.streams%b
   --  interfaces.c%s
   --  system.multiprocessors%b
   --  interfaces.c.extensions%s
   --  system.exceptions%s
   --  system.exceptions%b
   --  system.exceptions.machine%s
   --  system.file_control_block%s
   --  system.file_io%s
   --  system.finalization_root%s
   --  system.finalization_root%b
   --  ada.finalization%s
   --  ada.finalization%b
   --  system.linux%s
   --  system.os_constants%s
   --  system.os_interface%s
   --  system.os_interface%b
   --  system.interrupt_management%s
   --  system.task_info%s
   --  system.task_info%b
   --  system.task_primitives%s
   --  system.interrupt_management%b
   --  system.tasking%s
   --  system.task_primitives.operations%s
   --  system.tasking%b
   --  system.tasking.debug%s
   --  system.tasking.debug%b
   --  system.task_primitives.operations%b
   --  system.traces.tasking%s
   --  system.traces.tasking%b
   --  system.memory%s
   --  system.memory%b
   --  system.standard_library%b
   --  system.secondary_stack%s
   --  system.file_io%b
   --  interfaces.c%b
   --  ada.tags%b
   --  system.soft_links%b
   --  system.os_lib%b
   --  system.secondary_stack%b
   --  system.address_image%b
   --  system.soft_links.tasking%s
   --  system.soft_links.tasking%b
   --  system.tasking.entry_calls%s
   --  system.tasking.initialization%s
   --  system.tasking.task_attributes%s
   --  system.tasking.task_attributes%b
   --  system.tasking.utilities%s
   --  system.traceback%s
   --  ada.exceptions%b
   --  system.traceback%b
   --  system.tasking.initialization%b
   --  ada.real_time%s
   --  ada.real_time%b
   --  ada.text_io%s
   --  ada.text_io%b
   --  system.tasking.protected_objects%s
   --  system.tasking.protected_objects%b
   --  system.tasking.protected_objects.entries%s
   --  system.tasking.protected_objects.entries%b
   --  system.tasking.queuing%s
   --  system.tasking.queuing%b
   --  system.tasking.utilities%b
   --  system.tasking.rendezvous%s
   --  system.tasking.protected_objects.operations%s
   --  system.tasking.protected_objects.operations%b
   --  system.tasking.rendezvous%b
   --  system.tasking.entry_calls%b
   --  system.tasking.stages%s
   --  system.tasking.stages%b
   --  main%b
   --  END ELABORATION ORDER


end ada_main;
