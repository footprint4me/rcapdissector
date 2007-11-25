#include <winsock2.h>
#include <windows.h>

#include "rcapdissector.h"

#include "CapFile.h"
#include "NativePacket.h"
#include "Field.h"
#include "FieldQuery.h"
#include "NativePointer.h"
#include "YamlGenerator.h"

VALUE g_packet_class;
VALUE g_protocol_class;
VALUE g_field_class;
VALUE g_field_query_class;
VALUE g_capfile_error_class;
VALUE g_wtapcapfile_error_class;
VALUE g_field_doesnt_match_error_class;

VALUE g_add_element_func;
VALUE g_at_func;

VALUE g_cap_dissector_module;
VALUE g_cap_file_class;
VALUE g_native_pointer_class;

ID g_id_call;

extern "C" __declspec(dllexport) void Init_capdissector() {
    //Find the native-ruby companion classes that we need
    rb_require("capdissector");

	CapFile::initPacketCapture();

    g_capfile_error_class = rb_path2class("CapDissector::CapFileError");
    g_wtapcapfile_error_class = rb_path2class("CapDissector::WtapCapFileError");
	g_field_doesnt_match_error_class = rb_path2class("CapDissector::FieldDoesNotMatchQueryError");

    //Define the 'CapDissector' module
    g_cap_dissector_module = rb_define_module("CapDissector");

	//Define the CapFile class
	g_cap_file_class = CapFile::createClass();
	g_packet_class = Packet::createClass();
	g_field_class = Field::createClass();
	g_field_query_class = FieldQuery::createClass();
	g_native_pointer_class = NativePointer::createClass();

	g_id_call = ::rb_intern("call");
}

