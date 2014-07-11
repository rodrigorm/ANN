
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Ann_Visitor) {

	ZEPHIR_REGISTER_INTERFACE(Ann, Visitor, ann, visitor, ann_visitor_method_entry);

	return SUCCESS;

}

ZEPHIR_DOC_METHOD(Ann_Visitor, visitNetwork);

ZEPHIR_DOC_METHOD(Ann_Visitor, visitNeuron);

ZEPHIR_DOC_METHOD(Ann_Visitor, visitPeripheral);

ZEPHIR_DOC_METHOD(Ann_Visitor, visitBias);

ZEPHIR_DOC_METHOD(Ann_Visitor, visitDendrite);

ZEPHIR_DOC_METHOD(Ann_Visitor, visitSynapse);

