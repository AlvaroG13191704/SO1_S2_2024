// Code generated by protoc-gen-go. DO NOT EDIT.
// versions:
// 	protoc-gen-go v1.35.1
// 	protoc        v3.19.6
// source: client.proto

package confproto

import (
	protoreflect "google.golang.org/protobuf/reflect/protoreflect"
	protoimpl "google.golang.org/protobuf/runtime/protoimpl"
	reflect "reflect"
	sync "sync"
)

const (
	// Verify that this generated code is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(20 - protoimpl.MinVersion)
	// Verify that runtime/protoimpl is sufficiently up-to-date.
	_ = protoimpl.EnforceVersion(protoimpl.MaxVersion - 20)
)

type Discipline int32

const (
	Discipline_swimming Discipline = 0
	Discipline_boxing   Discipline = 1
)

// Enum value maps for Discipline.
var (
	Discipline_name = map[int32]string{
		0: "swimming",
		1: "boxing",
	}
	Discipline_value = map[string]int32{
		"swimming": 0,
		"boxing":   1,
	}
)

func (x Discipline) Enum() *Discipline {
	p := new(Discipline)
	*p = x
	return p
}

func (x Discipline) String() string {
	return protoimpl.X.EnumStringOf(x.Descriptor(), protoreflect.EnumNumber(x))
}

func (Discipline) Descriptor() protoreflect.EnumDescriptor {
	return file_client_proto_enumTypes[0].Descriptor()
}

func (Discipline) Type() protoreflect.EnumType {
	return &file_client_proto_enumTypes[0]
}

func (x Discipline) Number() protoreflect.EnumNumber {
	return protoreflect.EnumNumber(x)
}

// Deprecated: Use Discipline.Descriptor instead.
func (Discipline) EnumDescriptor() ([]byte, []int) {
	return file_client_proto_rawDescGZIP(), []int{0}
}

// Las estructuras de datos que se van a enviar
type StudentRequest struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Name       string     `protobuf:"bytes,1,opt,name=name,proto3" json:"name,omitempty"`
	Age        int32      `protobuf:"varint,3,opt,name=age,proto3" json:"age,omitempty"`
	Faculty    string     `protobuf:"bytes,2,opt,name=faculty,proto3" json:"faculty,omitempty"`
	Discipline Discipline `protobuf:"varint,4,opt,name=discipline,proto3,enum=confproto.Discipline" json:"discipline,omitempty"`
}

func (x *StudentRequest) Reset() {
	*x = StudentRequest{}
	mi := &file_client_proto_msgTypes[0]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *StudentRequest) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*StudentRequest) ProtoMessage() {}

func (x *StudentRequest) ProtoReflect() protoreflect.Message {
	mi := &file_client_proto_msgTypes[0]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use StudentRequest.ProtoReflect.Descriptor instead.
func (*StudentRequest) Descriptor() ([]byte, []int) {
	return file_client_proto_rawDescGZIP(), []int{0}
}

func (x *StudentRequest) GetName() string {
	if x != nil {
		return x.Name
	}
	return ""
}

func (x *StudentRequest) GetAge() int32 {
	if x != nil {
		return x.Age
	}
	return 0
}

func (x *StudentRequest) GetFaculty() string {
	if x != nil {
		return x.Faculty
	}
	return ""
}

func (x *StudentRequest) GetDiscipline() Discipline {
	if x != nil {
		return x.Discipline
	}
	return Discipline_swimming
}

type StudentResponse struct {
	state         protoimpl.MessageState
	sizeCache     protoimpl.SizeCache
	unknownFields protoimpl.UnknownFields

	Success string `protobuf:"bytes,1,opt,name=success,proto3" json:"success,omitempty"`
}

func (x *StudentResponse) Reset() {
	*x = StudentResponse{}
	mi := &file_client_proto_msgTypes[1]
	ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
	ms.StoreMessageInfo(mi)
}

func (x *StudentResponse) String() string {
	return protoimpl.X.MessageStringOf(x)
}

func (*StudentResponse) ProtoMessage() {}

func (x *StudentResponse) ProtoReflect() protoreflect.Message {
	mi := &file_client_proto_msgTypes[1]
	if x != nil {
		ms := protoimpl.X.MessageStateOf(protoimpl.Pointer(x))
		if ms.LoadMessageInfo() == nil {
			ms.StoreMessageInfo(mi)
		}
		return ms
	}
	return mi.MessageOf(x)
}

// Deprecated: Use StudentResponse.ProtoReflect.Descriptor instead.
func (*StudentResponse) Descriptor() ([]byte, []int) {
	return file_client_proto_rawDescGZIP(), []int{1}
}

func (x *StudentResponse) GetSuccess() string {
	if x != nil {
		return x.Success
	}
	return ""
}

var File_client_proto protoreflect.FileDescriptor

var file_client_proto_rawDesc = []byte{
	0x0a, 0x0c, 0x63, 0x6c, 0x69, 0x65, 0x6e, 0x74, 0x2e, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x12, 0x09,
	0x63, 0x6f, 0x6e, 0x66, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x22, 0x87, 0x01, 0x0a, 0x0e, 0x53, 0x74,
	0x75, 0x64, 0x65, 0x6e, 0x74, 0x52, 0x65, 0x71, 0x75, 0x65, 0x73, 0x74, 0x12, 0x12, 0x0a, 0x04,
	0x6e, 0x61, 0x6d, 0x65, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x04, 0x6e, 0x61, 0x6d, 0x65,
	0x12, 0x10, 0x0a, 0x03, 0x61, 0x67, 0x65, 0x18, 0x03, 0x20, 0x01, 0x28, 0x05, 0x52, 0x03, 0x61,
	0x67, 0x65, 0x12, 0x18, 0x0a, 0x07, 0x66, 0x61, 0x63, 0x75, 0x6c, 0x74, 0x79, 0x18, 0x02, 0x20,
	0x01, 0x28, 0x09, 0x52, 0x07, 0x66, 0x61, 0x63, 0x75, 0x6c, 0x74, 0x79, 0x12, 0x35, 0x0a, 0x0a,
	0x64, 0x69, 0x73, 0x63, 0x69, 0x70, 0x6c, 0x69, 0x6e, 0x65, 0x18, 0x04, 0x20, 0x01, 0x28, 0x0e,
	0x32, 0x15, 0x2e, 0x63, 0x6f, 0x6e, 0x66, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x2e, 0x44, 0x69, 0x73,
	0x63, 0x69, 0x70, 0x6c, 0x69, 0x6e, 0x65, 0x52, 0x0a, 0x64, 0x69, 0x73, 0x63, 0x69, 0x70, 0x6c,
	0x69, 0x6e, 0x65, 0x22, 0x2b, 0x0a, 0x0f, 0x53, 0x74, 0x75, 0x64, 0x65, 0x6e, 0x74, 0x52, 0x65,
	0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x12, 0x18, 0x0a, 0x07, 0x73, 0x75, 0x63, 0x63, 0x65, 0x73,
	0x73, 0x18, 0x01, 0x20, 0x01, 0x28, 0x09, 0x52, 0x07, 0x73, 0x75, 0x63, 0x63, 0x65, 0x73, 0x73,
	0x2a, 0x26, 0x0a, 0x0a, 0x44, 0x69, 0x73, 0x63, 0x69, 0x70, 0x6c, 0x69, 0x6e, 0x65, 0x12, 0x0c,
	0x0a, 0x08, 0x73, 0x77, 0x69, 0x6d, 0x6d, 0x69, 0x6e, 0x67, 0x10, 0x00, 0x12, 0x0a, 0x0a, 0x06,
	0x62, 0x6f, 0x78, 0x69, 0x6e, 0x67, 0x10, 0x01, 0x32, 0x55, 0x0a, 0x0e, 0x53, 0x74, 0x75, 0x64,
	0x65, 0x6e, 0x74, 0x53, 0x65, 0x72, 0x76, 0x69, 0x63, 0x65, 0x12, 0x43, 0x0a, 0x0a, 0x47, 0x65,
	0x74, 0x53, 0x74, 0x75, 0x64, 0x65, 0x6e, 0x74, 0x12, 0x19, 0x2e, 0x63, 0x6f, 0x6e, 0x66, 0x70,
	0x72, 0x6f, 0x74, 0x6f, 0x2e, 0x53, 0x74, 0x75, 0x64, 0x65, 0x6e, 0x74, 0x52, 0x65, 0x71, 0x75,
	0x65, 0x73, 0x74, 0x1a, 0x1a, 0x2e, 0x63, 0x6f, 0x6e, 0x66, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x2e,
	0x53, 0x74, 0x75, 0x64, 0x65, 0x6e, 0x74, 0x52, 0x65, 0x73, 0x70, 0x6f, 0x6e, 0x73, 0x65, 0x42,
	0x0e, 0x5a, 0x0c, 0x2e, 0x2f, 0x3b, 0x63, 0x6f, 0x6e, 0x66, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x62,
	0x06, 0x70, 0x72, 0x6f, 0x74, 0x6f, 0x33,
}

var (
	file_client_proto_rawDescOnce sync.Once
	file_client_proto_rawDescData = file_client_proto_rawDesc
)

func file_client_proto_rawDescGZIP() []byte {
	file_client_proto_rawDescOnce.Do(func() {
		file_client_proto_rawDescData = protoimpl.X.CompressGZIP(file_client_proto_rawDescData)
	})
	return file_client_proto_rawDescData
}

var file_client_proto_enumTypes = make([]protoimpl.EnumInfo, 1)
var file_client_proto_msgTypes = make([]protoimpl.MessageInfo, 2)
var file_client_proto_goTypes = []any{
	(Discipline)(0),         // 0: confproto.Discipline
	(*StudentRequest)(nil),  // 1: confproto.StudentRequest
	(*StudentResponse)(nil), // 2: confproto.StudentResponse
}
var file_client_proto_depIdxs = []int32{
	0, // 0: confproto.StudentRequest.discipline:type_name -> confproto.Discipline
	1, // 1: confproto.StudentService.GetStudent:input_type -> confproto.StudentRequest
	2, // 2: confproto.StudentService.GetStudent:output_type -> confproto.StudentResponse
	2, // [2:3] is the sub-list for method output_type
	1, // [1:2] is the sub-list for method input_type
	1, // [1:1] is the sub-list for extension type_name
	1, // [1:1] is the sub-list for extension extendee
	0, // [0:1] is the sub-list for field type_name
}

func init() { file_client_proto_init() }
func file_client_proto_init() {
	if File_client_proto != nil {
		return
	}
	type x struct{}
	out := protoimpl.TypeBuilder{
		File: protoimpl.DescBuilder{
			GoPackagePath: reflect.TypeOf(x{}).PkgPath(),
			RawDescriptor: file_client_proto_rawDesc,
			NumEnums:      1,
			NumMessages:   2,
			NumExtensions: 0,
			NumServices:   1,
		},
		GoTypes:           file_client_proto_goTypes,
		DependencyIndexes: file_client_proto_depIdxs,
		EnumInfos:         file_client_proto_enumTypes,
		MessageInfos:      file_client_proto_msgTypes,
	}.Build()
	File_client_proto = out.File
	file_client_proto_rawDesc = nil
	file_client_proto_goTypes = nil
	file_client_proto_depIdxs = nil
}
