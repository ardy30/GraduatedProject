// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: bc_master.protocol.proto

#ifndef PROTOBUF_bc_5fmaster_2eprotocol_2eproto__INCLUDED
#define PROTOBUF_bc_5fmaster_2eprotocol_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2004001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/generated_message_reflection.h>
// @@protoc_insertion_point(includes)

namespace bc_master {

// Internal implementation detail -- do not call these.
void  protobuf_AddDesc_bc_5fmaster_2eprotocol_2eproto();
void protobuf_AssignDesc_bc_5fmaster_2eprotocol_2eproto();
void protobuf_ShutdownFile_bc_5fmaster_2eprotocol_2eproto();

class pb_MSG_BC_MASTER_APPLY;
class pb_MSG_BC_MASTER_APPLY_ACK;

// ===================================================================

class pb_MSG_BC_MASTER_APPLY : public ::google::protobuf::Message {
 public:
  pb_MSG_BC_MASTER_APPLY();
  virtual ~pb_MSG_BC_MASTER_APPLY();
  
  pb_MSG_BC_MASTER_APPLY(const pb_MSG_BC_MASTER_APPLY& from);
  
  inline pb_MSG_BC_MASTER_APPLY& operator=(const pb_MSG_BC_MASTER_APPLY& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const pb_MSG_BC_MASTER_APPLY& default_instance();
  
  void Swap(pb_MSG_BC_MASTER_APPLY* other);
  
  // implements Message ----------------------------------------------
  
  pb_MSG_BC_MASTER_APPLY* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const pb_MSG_BC_MASTER_APPLY& from);
  void MergeFrom(const pb_MSG_BC_MASTER_APPLY& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // required string InstanceID = 1;
  inline bool has_instanceid() const;
  inline void clear_instanceid();
  static const int kInstanceIDFieldNumber = 1;
  inline const ::std::string& instanceid() const;
  inline void set_instanceid(const ::std::string& value);
  inline void set_instanceid(const char* value);
  inline void set_instanceid(const char* value, size_t size);
  inline ::std::string* mutable_instanceid();
  inline ::std::string* release_instanceid();
  
  // required int32 number = 2;
  inline bool has_number() const;
  inline void clear_number();
  static const int kNumberFieldNumber = 2;
  inline ::google::protobuf::int32 number() const;
  inline void set_number(::google::protobuf::int32 value);
  
  // @@protoc_insertion_point(class_scope:bc_master.pb_MSG_BC_MASTER_APPLY)
 private:
  inline void set_has_instanceid();
  inline void clear_has_instanceid();
  inline void set_has_number();
  inline void clear_has_number();
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::std::string* instanceid_;
  ::google::protobuf::int32 number_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(2 + 31) / 32];
  
  friend void  protobuf_AddDesc_bc_5fmaster_2eprotocol_2eproto();
  friend void protobuf_AssignDesc_bc_5fmaster_2eprotocol_2eproto();
  friend void protobuf_ShutdownFile_bc_5fmaster_2eprotocol_2eproto();
  
  void InitAsDefaultInstance();
  static pb_MSG_BC_MASTER_APPLY* default_instance_;
};
// -------------------------------------------------------------------

class pb_MSG_BC_MASTER_APPLY_ACK : public ::google::protobuf::Message {
 public:
  pb_MSG_BC_MASTER_APPLY_ACK();
  virtual ~pb_MSG_BC_MASTER_APPLY_ACK();
  
  pb_MSG_BC_MASTER_APPLY_ACK(const pb_MSG_BC_MASTER_APPLY_ACK& from);
  
  inline pb_MSG_BC_MASTER_APPLY_ACK& operator=(const pb_MSG_BC_MASTER_APPLY_ACK& from) {
    CopyFrom(from);
    return *this;
  }
  
  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _unknown_fields_;
  }
  
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return &_unknown_fields_;
  }
  
  static const ::google::protobuf::Descriptor* descriptor();
  static const pb_MSG_BC_MASTER_APPLY_ACK& default_instance();
  
  void Swap(pb_MSG_BC_MASTER_APPLY_ACK* other);
  
  // implements Message ----------------------------------------------
  
  pb_MSG_BC_MASTER_APPLY_ACK* New() const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const pb_MSG_BC_MASTER_APPLY_ACK& from);
  void MergeFrom(const pb_MSG_BC_MASTER_APPLY_ACK& from);
  void Clear();
  bool IsInitialized() const;
  
  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const;
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  public:
  
  ::google::protobuf::Metadata GetMetadata() const;
  
  // nested types ----------------------------------------------------
  
  // accessors -------------------------------------------------------
  
  // repeated string IP = 1;
  inline int ip_size() const;
  inline void clear_ip();
  static const int kIPFieldNumber = 1;
  inline const ::std::string& ip(int index) const;
  inline ::std::string* mutable_ip(int index);
  inline void set_ip(int index, const ::std::string& value);
  inline void set_ip(int index, const char* value);
  inline void set_ip(int index, const char* value, size_t size);
  inline ::std::string* add_ip();
  inline void add_ip(const ::std::string& value);
  inline void add_ip(const char* value);
  inline void add_ip(const char* value, size_t size);
  inline const ::google::protobuf::RepeatedPtrField< ::std::string>& ip() const;
  inline ::google::protobuf::RepeatedPtrField< ::std::string>* mutable_ip();
  
  // @@protoc_insertion_point(class_scope:bc_master.pb_MSG_BC_MASTER_APPLY_ACK)
 private:
  
  ::google::protobuf::UnknownFieldSet _unknown_fields_;
  
  ::google::protobuf::RepeatedPtrField< ::std::string> ip_;
  
  mutable int _cached_size_;
  ::google::protobuf::uint32 _has_bits_[(1 + 31) / 32];
  
  friend void  protobuf_AddDesc_bc_5fmaster_2eprotocol_2eproto();
  friend void protobuf_AssignDesc_bc_5fmaster_2eprotocol_2eproto();
  friend void protobuf_ShutdownFile_bc_5fmaster_2eprotocol_2eproto();
  
  void InitAsDefaultInstance();
  static pb_MSG_BC_MASTER_APPLY_ACK* default_instance_;
};
// ===================================================================


// ===================================================================

// pb_MSG_BC_MASTER_APPLY

// required string InstanceID = 1;
inline bool pb_MSG_BC_MASTER_APPLY::has_instanceid() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void pb_MSG_BC_MASTER_APPLY::set_has_instanceid() {
  _has_bits_[0] |= 0x00000001u;
}
inline void pb_MSG_BC_MASTER_APPLY::clear_has_instanceid() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void pb_MSG_BC_MASTER_APPLY::clear_instanceid() {
  if (instanceid_ != &::google::protobuf::internal::kEmptyString) {
    instanceid_->clear();
  }
  clear_has_instanceid();
}
inline const ::std::string& pb_MSG_BC_MASTER_APPLY::instanceid() const {
  return *instanceid_;
}
inline void pb_MSG_BC_MASTER_APPLY::set_instanceid(const ::std::string& value) {
  set_has_instanceid();
  if (instanceid_ == &::google::protobuf::internal::kEmptyString) {
    instanceid_ = new ::std::string;
  }
  instanceid_->assign(value);
}
inline void pb_MSG_BC_MASTER_APPLY::set_instanceid(const char* value) {
  set_has_instanceid();
  if (instanceid_ == &::google::protobuf::internal::kEmptyString) {
    instanceid_ = new ::std::string;
  }
  instanceid_->assign(value);
}
inline void pb_MSG_BC_MASTER_APPLY::set_instanceid(const char* value, size_t size) {
  set_has_instanceid();
  if (instanceid_ == &::google::protobuf::internal::kEmptyString) {
    instanceid_ = new ::std::string;
  }
  instanceid_->assign(reinterpret_cast<const char*>(value), size);
}
inline ::std::string* pb_MSG_BC_MASTER_APPLY::mutable_instanceid() {
  set_has_instanceid();
  if (instanceid_ == &::google::protobuf::internal::kEmptyString) {
    instanceid_ = new ::std::string;
  }
  return instanceid_;
}
inline ::std::string* pb_MSG_BC_MASTER_APPLY::release_instanceid() {
  clear_has_instanceid();
  if (instanceid_ == &::google::protobuf::internal::kEmptyString) {
    return NULL;
  } else {
    ::std::string* temp = instanceid_;
    instanceid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
    return temp;
  }
}

// required int32 number = 2;
inline bool pb_MSG_BC_MASTER_APPLY::has_number() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void pb_MSG_BC_MASTER_APPLY::set_has_number() {
  _has_bits_[0] |= 0x00000002u;
}
inline void pb_MSG_BC_MASTER_APPLY::clear_has_number() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void pb_MSG_BC_MASTER_APPLY::clear_number() {
  number_ = 0;
  clear_has_number();
}
inline ::google::protobuf::int32 pb_MSG_BC_MASTER_APPLY::number() const {
  return number_;
}
inline void pb_MSG_BC_MASTER_APPLY::set_number(::google::protobuf::int32 value) {
  set_has_number();
  number_ = value;
}

// -------------------------------------------------------------------

// pb_MSG_BC_MASTER_APPLY_ACK

// repeated string IP = 1;
inline int pb_MSG_BC_MASTER_APPLY_ACK::ip_size() const {
  return ip_.size();
}
inline void pb_MSG_BC_MASTER_APPLY_ACK::clear_ip() {
  ip_.Clear();
}
inline const ::std::string& pb_MSG_BC_MASTER_APPLY_ACK::ip(int index) const {
  return ip_.Get(index);
}
inline ::std::string* pb_MSG_BC_MASTER_APPLY_ACK::mutable_ip(int index) {
  return ip_.Mutable(index);
}
inline void pb_MSG_BC_MASTER_APPLY_ACK::set_ip(int index, const ::std::string& value) {
  ip_.Mutable(index)->assign(value);
}
inline void pb_MSG_BC_MASTER_APPLY_ACK::set_ip(int index, const char* value) {
  ip_.Mutable(index)->assign(value);
}
inline void pb_MSG_BC_MASTER_APPLY_ACK::set_ip(int index, const char* value, size_t size) {
  ip_.Mutable(index)->assign(
    reinterpret_cast<const char*>(value), size);
}
inline ::std::string* pb_MSG_BC_MASTER_APPLY_ACK::add_ip() {
  return ip_.Add();
}
inline void pb_MSG_BC_MASTER_APPLY_ACK::add_ip(const ::std::string& value) {
  ip_.Add()->assign(value);
}
inline void pb_MSG_BC_MASTER_APPLY_ACK::add_ip(const char* value) {
  ip_.Add()->assign(value);
}
inline void pb_MSG_BC_MASTER_APPLY_ACK::add_ip(const char* value, size_t size) {
  ip_.Add()->assign(reinterpret_cast<const char*>(value), size);
}
inline const ::google::protobuf::RepeatedPtrField< ::std::string>&
pb_MSG_BC_MASTER_APPLY_ACK::ip() const {
  return ip_;
}
inline ::google::protobuf::RepeatedPtrField< ::std::string>*
pb_MSG_BC_MASTER_APPLY_ACK::mutable_ip() {
  return &ip_;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace bc_master

#ifndef SWIG
namespace google {
namespace protobuf {


}  // namespace google
}  // namespace protobuf
#endif  // SWIG

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_bc_5fmaster_2eprotocol_2eproto__INCLUDED