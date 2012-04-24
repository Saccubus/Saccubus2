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
#ifndef SACCUBUS_VF_VHEXT_H
#define SACCUBUS_VF_VHEXT_H
/*
 * ツールボックスのバージョン
 * DLLの中で確認しといた方がいい。
 */
#define TOOLBOX_VERSION 2

/*
 * 呼ばれるときに一緒についてくるtoolbox.
 * ここから動画の情報なんかも取得できる。
 */
typedef struct toolbox{
	//バージョン
	int version;
	double video_length;
} toolbox;

typedef struct vhext_frame{
	void *data;
	int linesize;
	int w;
	int h;
	double pts;
} vhext_frame;


#ifdef __cplusplus
extern "C" {
#endif

/*
 * 拡張vhookライブラリ用関数群定義
 */

//configure用
typedef int (FrameHookExtConfigure)(void **ctxp,const toolbox *tbox, int argc, char *argv[]);
typedef FrameHookExtConfigure *FrameHookExtConfigureFn;
extern FrameHookExtConfigure ExtConfigure;

//フレーム用
typedef void (FrameHookExtProcess)(void *ctx,const toolbox *tbox,vhext_frame *pict);
typedef FrameHookExtProcess *FrameHookExtProcessFn;
extern FrameHookExtProcess ExtProcess;

//終了時に呼ぶ
typedef void (FrameHookExtRelease)(void *ctx,const toolbox *tbox);
typedef FrameHookExtRelease *FrameHookExtReleaseFn;
extern FrameHookExtRelease ExtRelease;

#ifdef __cplusplus
}
#endif

#endif /* SACCUBUS_VF_VHEXT_H */
