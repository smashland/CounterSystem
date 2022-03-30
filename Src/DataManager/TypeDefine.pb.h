// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: TypeDefine.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_TypeDefine_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_TypeDefine_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3014000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3014000 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_TypeDefine_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_TypeDefine_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_TypeDefine_2eproto;
PROTOBUF_NAMESPACE_OPEN
PROTOBUF_NAMESPACE_CLOSE

enum CONN_TYPE : int {
  CONN_UNUSE = 0,
  SERIAL = 1,
  WIFI = 2,
  CONN_TYPE_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  CONN_TYPE_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool CONN_TYPE_IsValid(int value);
constexpr CONN_TYPE CONN_TYPE_MIN = CONN_UNUSE;
constexpr CONN_TYPE CONN_TYPE_MAX = WIFI;
constexpr int CONN_TYPE_ARRAYSIZE = CONN_TYPE_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* CONN_TYPE_descriptor();
template<typename T>
inline const std::string& CONN_TYPE_Name(T enum_t_value) {
  static_assert(::std::is_same<T, CONN_TYPE>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function CONN_TYPE_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    CONN_TYPE_descriptor(), enum_t_value);
}
inline bool CONN_TYPE_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, CONN_TYPE* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<CONN_TYPE>(
    CONN_TYPE_descriptor(), name, value);
}
enum GunType : int {
  NOGUN = 0,
  RIFLE = 1,
  PISTOL = 2,
  GRENAD = 4,
  MORTAR = 8,
  MINES = 16,
  SNIPER = 32,
  LAUNCHER = 64,
  SUBMACHINE = 128,
  GunType_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  GunType_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool GunType_IsValid(int value);
constexpr GunType GunType_MIN = NOGUN;
constexpr GunType GunType_MAX = SUBMACHINE;
constexpr int GunType_ARRAYSIZE = GunType_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* GunType_descriptor();
template<typename T>
inline const std::string& GunType_Name(T enum_t_value) {
  static_assert(::std::is_same<T, GunType>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function GunType_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    GunType_descriptor(), enum_t_value);
}
inline bool GunType_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, GunType* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<GunType>(
    GunType_descriptor(), name, value);
}
enum PERSON_PART : int {
  FREE = 0,
  HEAD = 1,
  CHEST = 2,
  ABDOMEN = 3,
  BACK = 4,
  LEFT_ARM = 5,
  RIGHT_ARM = 6,
  LEFT_LEG = 7,
  RIGHT_LEG = 8,
  PERSON_PART_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  PERSON_PART_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool PERSON_PART_IsValid(int value);
constexpr PERSON_PART PERSON_PART_MIN = FREE;
constexpr PERSON_PART PERSON_PART_MAX = RIGHT_LEG;
constexpr int PERSON_PART_ARRAYSIZE = PERSON_PART_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* PERSON_PART_descriptor();
template<typename T>
inline const std::string& PERSON_PART_Name(T enum_t_value) {
  static_assert(::std::is_same<T, PERSON_PART>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function PERSON_PART_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    PERSON_PART_descriptor(), enum_t_value);
}
inline bool PERSON_PART_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, PERSON_PART* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<PERSON_PART>(
    PERSON_PART_descriptor(), name, value);
}
enum Weapon_Type : int {
  UNLINK = 0,
  OK = 1,
  LOCK = 2,
  Weapon_Type_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  Weapon_Type_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool Weapon_Type_IsValid(int value);
constexpr Weapon_Type Weapon_Type_MIN = UNLINK;
constexpr Weapon_Type Weapon_Type_MAX = LOCK;
constexpr int Weapon_Type_ARRAYSIZE = Weapon_Type_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* Weapon_Type_descriptor();
template<typename T>
inline const std::string& Weapon_Type_Name(T enum_t_value) {
  static_assert(::std::is_same<T, Weapon_Type>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function Weapon_Type_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    Weapon_Type_descriptor(), enum_t_value);
}
inline bool Weapon_Type_Parse(
    ::PROTOBUF_NAMESPACE_ID::ConstStringParam name, Weapon_Type* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<Weapon_Type>(
    Weapon_Type_descriptor(), name, value);
}
// ===================================================================


// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::CONN_TYPE> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::CONN_TYPE>() {
  return ::CONN_TYPE_descriptor();
}
template <> struct is_proto_enum< ::GunType> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::GunType>() {
  return ::GunType_descriptor();
}
template <> struct is_proto_enum< ::PERSON_PART> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::PERSON_PART>() {
  return ::PERSON_PART_descriptor();
}
template <> struct is_proto_enum< ::Weapon_Type> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::Weapon_Type>() {
  return ::Weapon_Type_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_TypeDefine_2eproto
