#pragma once
/*------------------------------------------------------------------------------*
| <<< カメラクラス Camera >>>
*------------------------------------------------------------------------------*/
class Camera {
private:
	float px, py;
	float camera_px;
	float camera_py;
public:
	float get_x() { return camera_px; } // 中心座標を加味した位置
	float get_y() { return camera_py; }
	float get_rawx() { return px; }		// そのままの位置(なるべく使わないで)
	float get_rawy() { return py; }
	void  update();
};

extern Camera Cam;