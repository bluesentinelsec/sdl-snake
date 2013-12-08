/*****************************************************************************
 * STAGE                                                                     *
 * See: stage.h                                                              *
 *****************************************************************************/

#include "stage.h"

Stage make_stage (UpdateFunc update, RenderFunc render) {
	Stage ret;
	ret.update = update;
	ret.render = render;
	return ret;
}