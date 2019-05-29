// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: test.proto

#ifndef PROTOBUF_INCLUDED_test_2eproto
#define PROTOBUF_INCLUDED_test_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_test_2eproto 

namespace protobuf_test_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_test_2eproto
class SearchRequest;
class SearchRequestDefaultTypeInternal;
extern SearchRequestDefaultTypeInternal _SearchRequest_default_instance_;
namespace google {
namespace protobuf {
template<> ::SearchRequest* Arena::CreateMaybeMessage<::SearchRequest>(Arena*);
}  // namespace protobuf
}  // namespace google

// ===================================================================

class SearchRequest : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:SearchRequest) */ {
 public:
  SearchRequest();
  virtual ~SearchRequest();

  SearchRequest(const SearchRequest& from);

  inline SearchRequest& operator=(const SearchRequest& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SearchRequest(SearchRequest&& from) noexcept
    : SearchRequest() {
    *this = ::std::move(from);
  }

  inline SearchRequest& operator=(SearchRequest&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const SearchRequest& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SearchRequest* internal_default_instance() {
    return reinterpret_cast<const SearchRequest*>(
               &_SearchRequest_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(SearchRequest* other);
  friend void swap(SearchRequest& a, SearchRequest& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SearchRequest* New() const final {
    return CreateMaybeMessage<SearchRequest>(NULL);
  }

  SearchRequest* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SearchRequest>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SearchRequest& from);
  void MergeFrom(const SearchRequest& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SearchRequest* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string query = 1;
  void clear_query();
  static const int kQueryFieldNumber = 1;
  const ::std::string& query() const;
  void set_query(const ::std::string& value);
  #if LANG_CXX11
  void set_query(::std::string&& value);
  #endif
  void set_query(const char* value);
  void set_query(const char* value, size_t size);
  ::std::string* mutable_query();
  ::std::string* release_query();
  void set_allocated_query(::std::string* query);

  // int32 page_number = 2;
  void clear_page_number();
  static const int kPageNumberFieldNumber = 2;
  ::google::protobuf::int32 page_number() const;
  void set_page_number(::google::protobuf::int32 value);

  // int32 result_per_page = 3;
  void clear_result_per_page();
  static const int kResultPerPageFieldNumber = 3;
  ::google::protobuf::int32 result_per_page() const;
  void set_result_per_page(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:SearchRequest)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr query_;
  ::google::protobuf::int32 page_number_;
  ::google::protobuf::int32 result_per_page_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_test_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SearchRequest

// string query = 1;
inline void SearchRequest::clear_query() {
  query_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& SearchRequest::query() const {
  // @@protoc_insertion_point(field_get:SearchRequest.query)
  return query_.GetNoArena();
}
inline void SearchRequest::set_query(const ::std::string& value) {
  
  query_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:SearchRequest.query)
}
#if LANG_CXX11
inline void SearchRequest::set_query(::std::string&& value) {
  
  query_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:SearchRequest.query)
}
#endif
inline void SearchRequest::set_query(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  query_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:SearchRequest.query)
}
inline void SearchRequest::set_query(const char* value, size_t size) {
  
  query_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:SearchRequest.query)
}
inline ::std::string* SearchRequest::mutable_query() {
  
  // @@protoc_insertion_point(field_mutable:SearchRequest.query)
  return query_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* SearchRequest::release_query() {
  // @@protoc_insertion_point(field_release:SearchRequest.query)
  
  return query_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void SearchRequest::set_allocated_query(::std::string* query) {
  if (query != NULL) {
    
  } else {
    
  }
  query_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), query);
  // @@protoc_insertion_point(field_set_allocated:SearchRequest.query)
}

// int32 page_number = 2;
inline void SearchRequest::clear_page_number() {
  page_number_ = 0;
}
inline ::google::protobuf::int32 SearchRequest::page_number() const {
  // @@protoc_insertion_point(field_get:SearchRequest.page_number)
  return page_number_;
}
inline void SearchRequest::set_page_number(::google::protobuf::int32 value) {
  
  page_number_ = value;
  // @@protoc_insertion_point(field_set:SearchRequest.page_number)
}

// int32 result_per_page = 3;
inline void SearchRequest::clear_result_per_page() {
  result_per_page_ = 0;
}
inline ::google::protobuf::int32 SearchRequest::result_per_page() const {
  // @@protoc_insertion_point(field_get:SearchRequest.result_per_page)
  return result_per_page_;
}
inline void SearchRequest::set_result_per_page(::google::protobuf::int32 value) {
  
  result_per_page_ = value;
  // @@protoc_insertion_point(field_set:SearchRequest.result_per_page)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_test_2eproto
