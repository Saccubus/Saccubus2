/**
 * Saccubus
 * Copyright (C) 2012 psi
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SACCUBUS_FF_ADAPTER_H
#define SACCUBUS_FF_ADAPTER_H
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
extern SaccConfigureFn SaccConfigure;

// 与えられた動画サイズから、出力サイズを決定する。一度だけ、呼ばれる。
typedef int (SaccMeasureFn)(void *sacc, SaccToolBox *box, int srcWidth, int srcHeight, int* dstWidth, int* dstHeight);
typedef SaccMeasureFn *SaccMeasureFnPtr;
extern SaccMeasureFn SaccMeasure;

// フレームに画像を焼きこむ
typedef int (SaccProcessFn)(void *sacc, SaccToolBox *box, SaccFrame *pict);
typedef SaccProcessFn *SaccProcessFnPtr;
extern SaccProcessFn SaccProcess;

// 終了時に呼ぶ
typedef int (SaccReleaseFn)(void *sacc, SaccToolBox *box);
typedef SaccReleaseFn *SaccReleaseFnPtr;
extern SaccReleaseFn SaccRelease;

#ifdef __cplusplus
}
#endif
#endif /* INCLUDE_GUARD */
