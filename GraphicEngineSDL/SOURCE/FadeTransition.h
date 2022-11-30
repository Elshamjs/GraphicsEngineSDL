#pragma once

#ifndef FADE_TRANSITION_H
#define FADE_TRANSITION_H

class FadeTransition : public Transition
{
private:
	float to_fade;
	float from_fade;
	void continue_process();
public:
	~FadeTransition();
	FadeTransition(VObject* target, float to_fade, float from_fade, float duration_s);
	FadeTransition(VObject* target, float to_fade, float from_fade, float duration_s, function<void()> on_finish);
	FadeTransition(VObject* target, float to_fade, float from_fade, float duration_s, int delay_millis);
	FadeTransition(VObject* target, float to_fade, float from_fade, float duration_s, int delay_millis, function<void()> on_finish);
	void play();
};
#endif // !FADE_TRANSITION_H