#ifndef __OCARINA_GENERATED_MARSHALLERS_H_
#define __OCARINA_GENERATED_MARSHALLERS_H_ 
/*****************************************************/

/*  This file was automatically generated by Ocarina */

/*  Do NOT hand-modify this file, as your            */

/*  changes will be lost when you re-run Ocarina     */

/*****************************************************/

void __po_hi_marshall_type_access_type 
    (threads__access_type value,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_unmarshall_type_access_type 
    (threads__access_type* value,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_marshall_type_booleanvalue 
    (threads__booleanvalue value,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_unmarshall_type_booleanvalue 
    (threads__booleanvalue* value,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_marshall_request_the_alarm_control_thread_access_type 
    (__po_hi_request_t* request,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_unmarshall_request_the_alarm_control_thread_access_type 
    (__po_hi_request_t* request,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_marshall_request_the_alarm_control_thread_turn_on_alarm 
    (__po_hi_request_t* request,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_unmarshall_request_the_alarm_control_thread_turn_on_alarm 
    (__po_hi_request_t* request,
    __po_hi_msg_t* message,
    __po_hi_uint32_t* offset);

void __po_hi_marshall_request 
    (__po_hi_request_t* request,
    __po_hi_msg_t* message);

void __po_hi_unmarshall_request 
    (__po_hi_request_t* request,
    __po_hi_msg_t* message);

#endif
