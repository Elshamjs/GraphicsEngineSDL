#pragma once

#ifndef SCALE_TRANSITION_H
#define SCALE_TRANSITION_H

class ScaleTransition : public Transition
{
public:
	~ScaleTransition();
	ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s);
	ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s, function<void()> on_finish);
	ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s, int delay_millis);
	ScaleTransition(VObject* target, float from_scale_x, float from_scale_y, float to_scale_x, float to_scale_y, float duration_s, int delay_millis, function<void()> on_finish);
	void play();
private:
	void continue_process();
	float to_scale_x;
	float to_scale_y;
	float from_scale_x;
	float from_scale_y;
};
#endif