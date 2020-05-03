//
// Created by madkne on 2020.5.2
//

#ifndef __MAHDI_IMPORTER_H
#define __MAHDI_IMPORTER_H  1

Boolean IMPORT_find_package_sources();
String IMPORT_get_file_package(String path);
Boolean IMPORT_start();
Boolean IMPORT_open_file(String path,Longint source_id);


//*************************************************************
//*******************import_inst functions*********************
//*************************************************************
Longint _imso_append(uint8 type,String name,String path,uint32 line,Longint source_id);
imso _imso_get(Longint id);


#endif /*__MAHDI_IMPORTER_H*/