/**
 * Autogenerated by Thrift
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 */
#ifndef shared_TYPES_H
#define shared_TYPES_H

/* base includes */
#include <glib-object.h>
#include "thrift_protocol.h"
#include "thrift_struct.h"


/* custom thrift includes */

/* begin types */

/* constants */

/* struct */
typedef struct _ThriftSharedStruct ThriftSharedStruct;
struct _ThriftSharedStruct
{ 
    ThriftStruct parent; 

    /* private */
    gint32 key;
    gchar * value;
}; 
typedef struct _ThriftSharedStructClass ThriftSharedStructClass;
struct _ThriftSharedStructClass
{ 
    ThriftStructClass parent; 
}; 
GType thrift_shared_struct_get_type (void);
#define THRIFT_TYPE_SHARED_STRUCT (thrift_shared_struct_get_type ())
#define THRIFT_SHARED_STRUCT(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), THRIFT_TYPE_SHARED_STRUCT, ThriftSharedStruct))
#define THRIFT_SHARED_STRUCT_CLASS(c) (G_TYPE_CHECK_CLASS_CAST ((c), THRIFT_TYPE_SHARED_STRUCT, ThriftSharedStructClass))
#define THRIFT_IS_SHARED_STRUCT(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), THRIFT_TYPE_SHARED_STRUCT))
#define THRIFT_IS_SHARED_STRUCT_CLASS(c) (G_TYPE_CHECK_CLASS_TYPE ((c), THRIFT_TYPE_SHARED_STRUCT))
#define THRIFT_SHARED_STRUCT_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), THRIFT_TYPE_SHARED_STRUCT, ThriftSharedStructClass))

#endif /* shared_TYPES_H */