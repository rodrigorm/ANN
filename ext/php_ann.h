
/* This file was generated automatically by Zephir do not modify it! */

#ifndef PHP_ANN_H
#define PHP_ANN_H 1

#define ZEPHIR_RELEASE 1

#include "kernel/globals.h"

#define PHP_ANN_NAME        "ann"
#define PHP_ANN_VERSION     "0.0.1"
#define PHP_ANN_EXTNAME     "ann"
#define PHP_ANN_AUTHOR      "Rodrigo Moyle"
#define PHP_ANN_ZEPVERSION  "0.4.1a"
#define PHP_ANN_DESCRIPTION ""



ZEND_BEGIN_MODULE_GLOBALS(ann)

	/* Memory */
	zephir_memory_entry *start_memory; /**< The first preallocated frame */
	zephir_memory_entry *end_memory; /**< The last preallocate frame */
	zephir_memory_entry *active_memory; /**< The current memory frame */

	/* Virtual Symbol Tables */
	zephir_symbol_table *active_symbol_table;

	/** Function cache */
	HashTable *fcache;

	/* Max recursion control */
	unsigned int recursive_lock;

	/* Global constants */
	zval *global_true;
	zval *global_false;
	zval *global_null;
	
ZEND_END_MODULE_GLOBALS(ann)

#ifdef ZTS
#include "TSRM.h"
#endif

ZEND_EXTERN_MODULE_GLOBALS(ann)

#ifdef ZTS
	#define ZEPHIR_GLOBAL(v) TSRMG(ann_globals_id, zend_ann_globals *, v)
#else
	#define ZEPHIR_GLOBAL(v) (ann_globals.v)
#endif

#ifdef ZTS
	#define ZEPHIR_VGLOBAL ((zend_ann_globals *) (*((void ***) tsrm_ls))[TSRM_UNSHUFFLE_RSRC_ID(ann_globals_id)])
#else
	#define ZEPHIR_VGLOBAL &(ann_globals)
#endif

#define zephir_globals ann_globals
#define zend_zephir_globals zend_ann_globals

extern zend_module_entry ann_module_entry;
#define phpext_ann_ptr &ann_module_entry

#endif
