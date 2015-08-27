#include<stdio.h>
#include<alsa/asoundlib.h>

int play_it()
{
	unsigned int 
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *params;
	snd_pcm_uframes_t frames;
	char *buffer;
	int buffer_side, loop;
	
	char *wav_fie = "/home/rafiq/program_c++/manzke/parse/audio/1_t.wav";
	
	if(pcm = snd_pcm_open(&pcm_handle,PCM_DEVICE,SND_PCM_STREAM_PLAYBACK, 0) < 0)
		printf("ERROR: Can't open %s device\n", PCM_DEVICE);
	
	snd_pcm_hw_params_alloca(&params);
	
	snd_pcm_hw_params_any(pcm_handle,params);
	
	if(pcm = snd_pcm_hw_params_set_access(pcm_handle,params,SND_PCM_ACCESS_RW_INTERLEAVED) < 0)
		printf("ERROR: Can't set interleaved %s\n",snd_strerror(pcm));
	
	if(pcm = snd_pcm_hw_params_set_format(pcm_handle,params,SND_PCM_ORMAT_S16_LE) < 0)
		printf("ERROR: can't set format %s\n",snd_strerror(pcm));
	
	if(pcm = snd_pcm_hw_params_set_rate(pcm_handle,params,sample_rate,0) < 0)
		printf("ERROR: Can't set rate %s\n",snd_strerror(pcm));
	
	if(pcm = snd_pcm_hw_params(pcm_handle,params) < 0)
		printf("ERROR: Can't set hardware parameters %s\n",snd_strerror(pcm));
	
	if(pcm = snd_pcm_hw_params_get_period_size(params, &frames, &dir))
		printf("ERROR: Can't get size of period %s\n",snd_strerror(pcm));
	
	buffer = malloc(frames *sfinfo.channels * sizeof(int));
	
	while((readcount = sf_readf_int(infile, buffer, frames))>0)
	{
		pcmrc = snd_pcm_writei(pcm_handle, buffer, readcount);
		if(pcmrc == -EPIPE)
		{
			printf("ERROR: Underrun\n");
			snd_pcm_prepare(pcm_handl);
		}
		else if(pcmrc < 0)
		{
			printf("ERROR: writing to PCM device %s\n",snd_strerror(pcmrc));
		}
		else if(pcmrc != readcount)
		{
			printf("ERROR: PCM write differes from PCM read\n");
		}
		
		snd_pcm_drain(pcm_handle);
		snd_pcm_close(pcm_handle);
		return 0;
	}
}