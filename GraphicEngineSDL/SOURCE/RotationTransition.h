#pragma once

#ifndef ROTATION_TRANSITION_H
#define ROTATION_TRANSITION_H

class RotationTransition : public Transition
{
public:
	~RotationTransition();
	RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s);
	RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s, function<void()> on_finish);
	RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s, int delay_millis);
	RotationTransition(VObject* target, float from_rotation, float to_rotation, float duration_s, int delay_millis, function<void()> on_finish);
	void play();

private:
	void continue_process();
	double from_rotation;
	double to_rotation;
};

#endif // !ROTATION_TRANSITION_H