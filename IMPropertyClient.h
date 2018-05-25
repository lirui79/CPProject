/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/05/09
**   File: IMPropertyClient.h
**   History:
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef IMODULE_IMPROPERTYCLIENT_H
#define IMODULE_IMPROPERTYCLIENT_H


#include "IModule.h"

#include <memory>

namespace iris {

enum TargetProductType {
	NoDevice = 0,
	ANGLER,
	PIXEL,
	HIAR,
	MT,
	RK,
	HALO,
	X1,
	x3399,
	Y1,
	SUMSEEN,
	XLOONG,
	PIXELXL,
	V1
};
}

/**
 * Guideline
 * group by project/folder, not meaning
 * the length of key should not be larger than 32
 *
 * ro : prefix for read only
 * hw : hardware related
 * sys : android source related
 * iris : iris-android-modules
 * win : iris-win
 * api : simple-sdk
 * unity : plugins like gvr
 */

// recommended texture size
#define PROP_API_SCREEN_WIDTH "api.screen.width"
#define PROP_API_SCREEN_HEIGHT "api.screen.height"
// actually these three are more close to ro.win.layer.*
#define PROP_API_SCREEN_SEPARATE "api.screen.separate"
#define PROP_API_SCREEN_ROTATE_DIRECTION "api.screen.rotate_direction"
#define PROP_API_SCREEN_LEFT_TO_RIGHT "api.screen.left_to_right"
#define PROP_RO_API_DISTORTION_SO "ro.api.distortion_so"
#define PROP_RO_API_TILING_QCOM "ro.api.tiling_qcom"
#define PROP_RO_API_SWAP_AFTER_DRAW "ro.api.swap_after_draw"
#define PROP_RO_API_FINISH_AFTER_DRAW "ro.api.finish_after_draw"
#define PROP_RO_API_CHANGE_RATIO "ro.api.change_ratio"
#define PROP_RO_API_MIDLINE_COLOR "ro.api.midline.color"

#define PROP_API_SCREEN_EXTERNAL_ROTATE_DIRECTION \
	"api.screen.external.rotate_direction"

// omit eye
// view matrix
#define PROP_API_LEFT_POS "api.left.pos"
#define PROP_API_LEFT_QUAT "api.left.quat"
#define PROP_API_RIGHT_POS "api.right.pos"
#define PROP_API_RIGHT_QUAT "api.right.quat"
// proj matrix
#define PROP_API_LEFT_FOV "api.left.fov"
#define PROP_API_LEFT_WH_RATIO "api.left.wh_ratio"
#define PROP_API_LEFT_PLANE_NEAR "api.left.plane.near"
#define PROP_API_LEFT_PLANE_FAR "api.left.plane.far"
#define PROP_API_RIGHT_FOV "api.right.fov"
#define PROP_API_RIGHT_WH_RATIO "api.right.wh_ratio"
#define PROP_API_RIGHT_PLANE_NEAR "api.right.plane.near"
#define PROP_API_RIGHT_PLANE_FAR "api.right.plane.far"

#define PROP_RO_HW_FPS "ro.hw.fps"

#define PROP_RO_SYS_APP_HEIGHT "ro.sys.app.height"
#define PROP_RO_SYS_APP_WIDTH "ro.sys.app.width"
#define PROP_RO_SYS_APP_DENSITY_SCALE "ro.sys.app.density.scale"
#define PROP_RO_SYS_APP_LOCK_LANDSCAPE "ro.sys.app.lock_landscape"
#define PROP_RO_SYS_IME_HAS_FULLSCREENAREA "ro.sys.ime.has_fullscreenarea"
#define PROP_RO_SYS_FAKE_SDK_24 "ro.sys.fake_sdk_24"
#define PROP_RO_SYS_BOOT_SUPPORT_START "ro.sys.boot.support_start"
#define PROP_RO_SYS_TARGET_PRODUCT "ro.sys.target.product"
#define PROP_RO_SYS_SERVICE_SENSOR_VALID "ro.sys.service.sensor.valid"

#define PROP_SYS_APP_MULTIPLE "sys.app.multiple"
#define PROP_SYS_IME_SEPARATE "sys.ime.separate"
#define PROP_RO_SYS_EXTERNAL_DISPLAY_SUPPORT "ro.sys.display.external.support"
#define PROP_SYS_EXTERNAL_DISPLAY_HEIGHT "sys.display.external.height"
#define PROP_SYS_EXTERNAL_DISPLAY_WIDTH "sys.display.external.width"

#define PROP_RO_IRIS_WIN_PROP_FLAG "ro.iris.win.prop_flag"
#define PROP_RO_IRIS_SYSTEMUI_HIDE "ro.iris.systemui.hide"
#define PROP_RO_IRIS_LAUNCHER_HIDE "ro.iris.launcher.hide"
#define PROP_RO_IRIS_VR_BUFFER "ro.iris.vr_buffer"

#define PROP_RO_NAVI_DEVICE_TYPE "navi.device.type"
#define PROP_NAVI_USE_NOLO_POS "navi.use.nolo.pos"
#define PROP_NAVI_USE_NOLO_QUA "navi.use.nolo.qua"

#define PROP_RO_SKIN_EULA_FONT_CHS "ro.skin.eula.font.chs"
#define PROP_RO_SKIN_EULA_FONT_ENG "ro.skin.eula.font.eng"
#define PROP_RO_SKIN_FB_SCENE_FORMAT "ro.skin.fb.scene_format"
#define PROP_RO_SKIN_FB_OVERLAY_FORMAT "ro.skin.fb.overlay_format"
#define PROP_RO_SKIN_FINISH_BEFORE_AA "ro.skin.finish_before_aa"
#define PROP_RO_SKIN_HAND_SIZE "ro.skin.hand.size"
#define PROP_RO_SKIN_HAND_COLOR "ro.skin.hand.color"
#define PROP_RO_SKIN_HAND_SCALE "ro.skin.hand.scale"

#define PROP_RO_UNITY_WATERMARK "ro.unity.watermark"

#define PROP_RO_WIN_FOLLOW_POSE_MIN_DIST "ro.win.follow_pose.min_dist"
#define PROP_RO_WIN_FOLLOW_POSE_FOLLOW_SPEED "ro.win.follow_pose.follow_speed"
#define PROP_RO_WIN_MOVE_ALONG_MIN_DIST "ro.win.move_along.min_dist"
#define PROP_RO_WIN_MOVE_ALONG_ABS_SPEED "ro.win.move_along.abs_speed"
#define PROP_RO_WIN_ROTATE_ABS_SPEED "ro.win.rotate.abs_speed"
#define PROP_RO_WIN_LAYER_WIDTH "ro.win.layer.width"
#define PROP_RO_WIN_LAYER_HEIGHT "ro.win.layer.height"
#define PROP_RO_WIN_LAYER_FORMAT "ro.win.layer.format"

// device info
#define PROP_RO_BUILD_VERSION_IRISOS "ro.bulid.version.irisos"
#define PROP_RO_BUILD_DEVICE_INFO "ro.bulid.device.info"
#define PROP_RO_BUILD_TYPE "ro.bulid.type"

// iris log
#define PROP_IRIS_LOG_TYPE "iris.log.type"



namespace iris {

class IMPropertyClient : public IModule {
   private:
	IMPropertyClient(const IMPropertyClient& module);

	IMPropertyClient& operator=(const IMPropertyClient& module);

   protected:
	IMPropertyClient() {}

   public:
	virtual ~IMPropertyClient() {}

	static SmartPtr<IMPropertyClient> singleton();

	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init() = 0;

	/**
	 * 退出模块内部线程，释放内存等
	 */
	virtual int exit() = 0;

	virtual int get(const char* key , int value = 0) = 0;

	virtual long get(const char* key , long value = 0) = 0;

	virtual bool get(const char* key , bool value = false) = 0;

	virtual const char* get(const char* key , const char* value = "") = 0;

	virtual double get(const char* key , double value = 0.0) = 0;

	virtual int get(const char* key , double *value , int &sz) = 0;

	virtual int set(const char* key, int value) = 0;

	virtual int set(const char* key, long value) = 0;

	virtual int set(const char* key, bool value) = 0;

	virtual int set(const char* key, const char* value) = 0;

	virtual int set(const char* key, double value) = 0;

	virtual int set(const char* key, const double* data, int sz) = 0;


	virtual const char* getClassName() const { return "IMPropertyClient"; }
};

}  // namespace iris

#endif