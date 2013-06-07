/* coding: utf-8 */
/**
 * Saccubus
 *
 * Copyright 2007-2013, PSI
 */

#ifndef SACCUBUS_FF_ADAPTER_H
#define SACCUBUS_FF_ADAPTER_H

#if ((defined(WIN32) || defined(WIN64) || defined(__WIN32__) || defined(__WIN64__)))

#if defined(SACC_DLL_EXPORT)
#define DYNAPI __declspec(dllexport)
#else
#define DYNAPI __declspec(dllimport)
#endif

#else
#define DYNAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * ツールボックスのバージョン
 * DLLの中で確認しといた方がいい。
 */
#define TOOLBOX_VERSION 2

/*
 * 呼ばれるときに一緒についてくるtoolbox.
 * ここから部分的にffmpegを操作することが可能
 */

typedef struct SaccToolBox SaccToolBox;
typedef struct SaccFrame SaccFrame;

struct SaccToolBox {
	/* 管理用 */
	void* ptr;
	/* バージョン */
	int version;
	int (*loadVideo)(SaccToolBox* box, const char* filename);
	int (*seek)(SaccToolBox* box, double pts);
	/* 現在の動画情報 */
	struct {
		int width;
		int height;
		double length;
	} currentVideo;
};

struct SaccFrame{
	/* 画像データ */
	double vpos;
	void *data;
	int linesize;
	int w;
	int h;
};

/*
 * 拡張vhookライブラリ用関数群定義
 */

// configure用
typedef int (SaccConfigureFn)(void **sacc, SaccToolBox *box, int argc, char *argv[]);
typedef SaccConfigureFn *SaccConfigureFnPtr;
#ifdef SACC_DLL_EXPORT
extern SaccConfigureFn DYNAPI SaccConfigure;
#endif

// 与えられた動画サイズから、出力サイズを決定する。一度だけ、呼ばれる。
typedef int (SaccMeasureFn)(void *sacc, SaccToolBox *box, int srcWidth, int srcHeight, int* dstWidth, int* dstHeight);
typedef SaccMeasureFn *SaccMeasureFnPtr;
#ifdef SACC_DLL_EXPORT
extern SaccMeasureFn DYNAPI SaccMeasure;
#endif

// フレームに画像を焼きこむ
typedef int (SaccProcessFn)(void *sacc, SaccToolBox *box, SaccFrame *target, SaccFrame* video);
typedef SaccProcessFn *SaccProcessFnPtr;
#ifdef SACC_DLL_EXPORT
extern SaccProcessFn DYNAPI SaccProcess;
#endif

// 終了時に呼ぶ
typedef int (SaccReleaseFn)(void *sacc, SaccToolBox *box);
typedef SaccReleaseFn *SaccReleaseFnPtr;
#ifdef SACC_DLL_EXPORT
extern SaccReleaseFn DYNAPI SaccRelease;
#endif

#ifdef __cplusplus
}
#endif
#endif /* INCLUDE_GUARD */
