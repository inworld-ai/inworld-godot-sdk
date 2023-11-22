#include "ProtoDisableWarning.h"
// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: grpc-stub/platform-public/src/main/proto/ai/inworld/engine/v1/state_serialization.proto

#include "grpc-stub/platform-public/src/main/proto/ai/inworld/engine/v1/state_serialization.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_google_2fprotobuf_2ftimestamp_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_Timestamp_google_2fprotobuf_2ftimestamp_2eproto;
namespace ai {
namespace inworld {
namespace engine {
namespace v1 {
class GetSessionStateRequestDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<GetSessionStateRequest> _instance;
} _GetSessionStateRequest_default_instance_;
class SessionStateDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<SessionState> _instance;
} _SessionState_default_instance_;
}  // namespace v1
}  // namespace engine
}  // namespace inworld
}  // namespace ai
static void InitDefaultsscc_info_GetSessionStateRequest_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::ai::inworld::engine::v1::_GetSessionStateRequest_default_instance_;
    new (ptr) ::ai::inworld::engine::v1::GetSessionStateRequest();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_GetSessionStateRequest_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_GetSessionStateRequest_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto}, {}};

static void InitDefaultsscc_info_SessionState_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::ai::inworld::engine::v1::_SessionState_default_instance_;
    new (ptr) ::ai::inworld::engine::v1::SessionState();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_SessionState_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_SessionState_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto}, {
      &scc_info_Timestamp_google_2fprotobuf_2ftimestamp_2eproto.base,}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ai::inworld::engine::v1::GetSessionStateRequest, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ai::inworld::engine::v1::GetSessionStateRequest, name_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ai::inworld::engine::v1::SessionState, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ai::inworld::engine::v1::SessionState, state_),
  PROTOBUF_FIELD_OFFSET(::ai::inworld::engine::v1::SessionState, creation_time_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::ai::inworld::engine::v1::GetSessionStateRequest)},
  { 6, -1, sizeof(::ai::inworld::engine::v1::SessionState)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ai::inworld::engine::v1::_GetSessionStateRequest_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ai::inworld::engine::v1::_SessionState_default_instance_),
};

const char descriptor_table_protodef_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\nWgrpc-stub/platform-public/src/main/pro"
  "to/ai/inworld/engine/v1/state_serializat"
  "ion.proto\022\024ai.inworld.engine.v1\032\034google/"
  "api/annotations.proto\032\027google/api/client"
  ".proto\032\037google/api/field_behavior.proto\032"
  "\031google/api/resource.proto\032\037google/proto"
  "buf/timestamp.proto\"Q\n\026GetSessionStateRe"
  "quest\0227\n\004name\030\001 \001(\tB)\340A\002\372A#\n!ai.inworld."
  "engine.v1/SessionState\"P\n\014SessionState\022\r"
  "\n\005state\030\001 \001(\014\0221\n\rcreation_time\030\002 \001(\0132\032.g"
  "oogle.protobuf.Timestamp2\263\001\n\022StateSerial"
  "ization\022\234\001\n\017GetSessionState\022,.ai.inworld"
  ".engine.v1.GetSessionStateRequest\032\".ai.i"
  "nworld.engine.v1.SessionState\"7\202\323\344\223\002*\022(/"
  "v1/{name=workspaces/*/sessions/*}/state\332"
  "A\004nameB\222\001\n\024ai.inworld.engine.v1B\027StateSe"
  "rializationProtoP\001ZHgithub.com/inworld-a"
  "i/inworld/serving/grpc-gateway/build/pro"
  "to/engine/v1\252\002\024Ai.Inworld.Engine.V1b\006pro"
  "to3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto_deps[5] = {
  &::descriptor_table_google_2fapi_2fannotations_2eproto,
  &::descriptor_table_google_2fapi_2fclient_2eproto,
  &::descriptor_table_google_2fapi_2ffield_5fbehavior_2eproto,
  &::descriptor_table_google_2fapi_2fresource_2eproto,
  &::descriptor_table_google_2fprotobuf_2ftimestamp_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto_sccs[2] = {
  &scc_info_GetSessionStateRequest_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto.base,
  &scc_info_SessionState_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto = {
  false, false, descriptor_table_protodef_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto, "grpc-stub/platform-public/src/main/proto/ai/inworld/engine/v1/state_serialization.proto", 763,
  &descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto_once, descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto_sccs, descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto_deps, 2, 5,
  schemas, file_default_instances, TableStruct_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto::offsets,
  file_level_metadata_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto, 2, file_level_enum_descriptors_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto, file_level_service_descriptors_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto)), true);
namespace ai {
namespace inworld {
namespace engine {
namespace v1 {

// ===================================================================

class GetSessionStateRequest::_Internal {
 public:
};

GetSessionStateRequest::GetSessionStateRequest(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ai.inworld.engine.v1.GetSessionStateRequest)
}
GetSessionStateRequest::GetSessionStateRequest(const GetSessionStateRequest& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_name().empty()) {
    name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(), 
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:ai.inworld.engine.v1.GetSessionStateRequest)
}

void GetSessionStateRequest::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_GetSessionStateRequest_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto.base);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

GetSessionStateRequest::~GetSessionStateRequest() {
  // @@protoc_insertion_point(destructor:ai.inworld.engine.v1.GetSessionStateRequest)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void GetSessionStateRequest::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void GetSessionStateRequest::ArenaDtor(void* object) {
  GetSessionStateRequest* _this = reinterpret_cast< GetSessionStateRequest* >(object);
  (void)_this;
}
void GetSessionStateRequest::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void GetSessionStateRequest::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const GetSessionStateRequest& GetSessionStateRequest::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_GetSessionStateRequest_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto.base);
  return *internal_default_instance();
}


void GetSessionStateRequest::Clear() {
// @@protoc_insertion_point(message_clear_start:ai.inworld.engine.v1.GetSessionStateRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  name_.ClearToEmpty();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* GetSessionStateRequest::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // string name = 1 [(.google.api.field_behavior) = REQUIRED, (.google.api.resource_reference) = {
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "ai.inworld.engine.v1.GetSessionStateRequest.name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* GetSessionStateRequest::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ai.inworld.engine.v1.GetSessionStateRequest)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // string name = 1 [(.google.api.field_behavior) = REQUIRED, (.google.api.resource_reference) = {
  if (this->name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ai.inworld.engine.v1.GetSessionStateRequest.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ai.inworld.engine.v1.GetSessionStateRequest)
  return target;
}

size_t GetSessionStateRequest::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ai.inworld.engine.v1.GetSessionStateRequest)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 1 [(.google.api.field_behavior) = REQUIRED, (.google.api.resource_reference) = {
  if (this->name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void GetSessionStateRequest::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ai.inworld.engine.v1.GetSessionStateRequest)
  GOOGLE_DCHECK_NE(&from, this);
  const GetSessionStateRequest* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<GetSessionStateRequest>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ai.inworld.engine.v1.GetSessionStateRequest)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ai.inworld.engine.v1.GetSessionStateRequest)
    MergeFrom(*source);
  }
}

void GetSessionStateRequest::MergeFrom(const GetSessionStateRequest& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ai.inworld.engine.v1.GetSessionStateRequest)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.name().size() > 0) {
    _internal_set_name(from._internal_name());
  }
}

void GetSessionStateRequest::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ai.inworld.engine.v1.GetSessionStateRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void GetSessionStateRequest::CopyFrom(const GetSessionStateRequest& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ai.inworld.engine.v1.GetSessionStateRequest)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GetSessionStateRequest::IsInitialized() const {
  return true;
}

void GetSessionStateRequest::InternalSwap(GetSessionStateRequest* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata GetSessionStateRequest::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

class SessionState::_Internal {
 public:
  static const PROTOBUF_NAMESPACE_ID::Timestamp& creation_time(const SessionState* msg);
};

const PROTOBUF_NAMESPACE_ID::Timestamp&
SessionState::_Internal::creation_time(const SessionState* msg) {
  return *msg->creation_time_;
}
void SessionState::clear_creation_time() {
  if (GetArena() == nullptr && creation_time_ != nullptr) {
    delete creation_time_;
  }
  creation_time_ = nullptr;
}
SessionState::SessionState(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ai.inworld.engine.v1.SessionState)
}
SessionState::SessionState(const SessionState& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  state_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_state().empty()) {
    state_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_state(), 
      GetArena());
  }
  if (from._internal_has_creation_time()) {
    creation_time_ = new PROTOBUF_NAMESPACE_ID::Timestamp(*from.creation_time_);
  } else {
    creation_time_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:ai.inworld.engine.v1.SessionState)
}

void SessionState::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_SessionState_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto.base);
  state_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  creation_time_ = nullptr;
}

SessionState::~SessionState() {
  // @@protoc_insertion_point(destructor:ai.inworld.engine.v1.SessionState)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void SessionState::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  state_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete creation_time_;
}

void SessionState::ArenaDtor(void* object) {
  SessionState* _this = reinterpret_cast< SessionState* >(object);
  (void)_this;
}
void SessionState::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void SessionState::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const SessionState& SessionState::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_SessionState_grpc_2dstub_2fplatform_2dpublic_2fsrc_2fmain_2fproto_2fai_2finworld_2fengine_2fv1_2fstate_5fserialization_2eproto.base);
  return *internal_default_instance();
}


void SessionState::Clear() {
// @@protoc_insertion_point(message_clear_start:ai.inworld.engine.v1.SessionState)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  state_.ClearToEmpty();
  if (GetArena() == nullptr && creation_time_ != nullptr) {
    delete creation_time_;
  }
  creation_time_ = nullptr;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* SessionState::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // bytes state = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_state();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .google.protobuf.Timestamp creation_time = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_creation_time(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* SessionState::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ai.inworld.engine.v1.SessionState)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // bytes state = 1;
  if (this->state().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_state(), target);
  }

  // .google.protobuf.Timestamp creation_time = 2;
  if (this->has_creation_time()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::creation_time(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ai.inworld.engine.v1.SessionState)
  return target;
}

size_t SessionState::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ai.inworld.engine.v1.SessionState)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bytes state = 1;
  if (this->state().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_state());
  }

  // .google.protobuf.Timestamp creation_time = 2;
  if (this->has_creation_time()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *creation_time_);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SessionState::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ai.inworld.engine.v1.SessionState)
  GOOGLE_DCHECK_NE(&from, this);
  const SessionState* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<SessionState>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ai.inworld.engine.v1.SessionState)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ai.inworld.engine.v1.SessionState)
    MergeFrom(*source);
  }
}

void SessionState::MergeFrom(const SessionState& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ai.inworld.engine.v1.SessionState)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.state().size() > 0) {
    _internal_set_state(from._internal_state());
  }
  if (from.has_creation_time()) {
    _internal_mutable_creation_time()->PROTOBUF_NAMESPACE_ID::Timestamp::MergeFrom(from._internal_creation_time());
  }
}

void SessionState::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ai.inworld.engine.v1.SessionState)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SessionState::CopyFrom(const SessionState& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ai.inworld.engine.v1.SessionState)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SessionState::IsInitialized() const {
  return true;
}

void SessionState::InternalSwap(SessionState* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  state_.Swap(&other->state_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  swap(creation_time_, other->creation_time_);
}

::PROTOBUF_NAMESPACE_ID::Metadata SessionState::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace v1
}  // namespace engine
}  // namespace inworld
}  // namespace ai
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ai::inworld::engine::v1::GetSessionStateRequest* Arena::CreateMaybeMessage< ::ai::inworld::engine::v1::GetSessionStateRequest >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ai::inworld::engine::v1::GetSessionStateRequest >(arena);
}
template<> PROTOBUF_NOINLINE ::ai::inworld::engine::v1::SessionState* Arena::CreateMaybeMessage< ::ai::inworld::engine::v1::SessionState >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ai::inworld::engine::v1::SessionState >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
