#pragma once
/*------------------------------------------------------------------------------*
| <<< �J�����N���X Camera >>>
*------------------------------------------------------------------------------*/
class Camera {
private:
	float px, py;
	float camera_px;
	float camera_py;
public:
	float get_x() { return camera_px; } // ���S���W�����������ʒu
	float get_y() { return camera_py; }
	float get_rawx() { return px; }		// ���̂܂܂̈ʒu(�Ȃ�ׂ��g��Ȃ���)
	float get_rawy() { return py; }
	void  update();
};

extern Camera Cam;