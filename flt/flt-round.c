#include "flt-tmp.h"

static void flt_tmp_ceil(flt_tmp *pt);
static void flt_tmp_floor(flt_tmp *pt);

FLT flt_ceil(const FLT f) {
	FLT result;
	flt_tmp t;
	int sign;
	flt_to_tmp(&f, &t);
	if (t.c == E_NORMAL) {
		sign = t.s;
		t.s = 0;
		if (sign)
			flt_tmp_floor(&t);
		else
			flt_tmp_ceil(&t);
		t.s = sign;
		tmp_to_flt(&t, &result);
	} else
		result = f;
	return result;	
}

FLT flt_floor(const FLT f) {
	FLT result;
	flt_tmp t;
	int sign;
	flt_to_tmp(&f, &t);
	if (t.c == E_NORMAL) {
		sign = t.s;
		t.s = 0;
		if (sign)
			flt_tmp_ceil(&t);
		else
			flt_tmp_floor(&t);
		t.s = sign;
		tmp_to_flt(&t, &result);
	} else
		result = f;
	return result;	
}

static void flt_tmp_ceil(flt_tmp *pt) {
	flt_tmp u;
	flt_tmp_copy(&u, pt);
	flt_tmp_modf(&u, pt);
	if (u.c == E_NORMAL) {
		flt_tmp_initialize(&u, E_NORMAL, 0, TMP_1, 0);
		flt_tmp_add(pt, &u);
	}
}

static void flt_tmp_floor(flt_tmp *pt) {
	flt_tmp u;
	flt_tmp_copy(&u, pt);
	flt_tmp_modf(&u, pt);
}
