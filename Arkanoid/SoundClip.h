#pragma once

class SoundClip
{
public:

	~SoundClip();
	SoundClip(Mix_Chunk* p_pxClip);

	void Play();
	void Pause();
	void Stop();
	void Volume(int p_iVolume);

private:

	SoundClip();
	
	Mix_Chunk* m_pxClip;
	int m_iChannel;
};