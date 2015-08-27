#include<stdio.h>
#include<alsa/asoundlib.h>

int main()
{
	int err,rate = 8000,i = 0,c;
	int buf[128];
	FILE *afile;
	snd_pcm_t *pcm_handle;
	snd_pcm_hw_params_t *params;
	size_t nread;
	char* dir = "aud/"; 
	char* extension = ".wav";
	char fileSpec[strlen(dir)+strlen(extension)+3];
	
	if((err = snd_pcm_open(&pcm_handle,"plughw:0,0",SND_PCM_STREAM_PLAYBACK,0)) < 0)
	{
		fprintf(stderr,"Can't open the sound device %s",snd_strerror(err));
		return err;
	}
	
	snd_pcm_hw_params_alloca(&params);
	snd_pcm_hw_params_any(pcm_handle,params);
	snd_pcm_hw_params_set_access(pcm_handle,params,SND_PCM_ACCESS_RW_INTERLEAVED);
	snd_pcm_hw_params_set_format(pcm_handle,params,SND_PCM_FORMAT_S16_LE);
	snd_pcm_hw_params_set_channels(pcm_handle,params,1);
	snd_pcm_hw_params_set_rate_near(pcm_handle,params,&rate,NULL);
	
	if((err = snd_pcm_hw_params(pcm_handle,params)) < 0)
	{
		fprintf(stderr,"Can't set parameters for sound %s\n",snd_strerror(err));
		return err;
	}
	
	for (i; i<100;i++)
	{
	    snprintf(fileSpec, sizeof( fileSpec ), "%s%d%s", dir, i, extension );
	    		
		afile = fopen(fileSpec, "r");
		
		if(afile == NULL)
			{
				fprintf(stderr,"Can't Open file for reading\n");
				return 1;
			}
	
		while ((nread = fread(buf, sizeof(int), 128, afile)) > 0)
		{
			if((err = snd_pcm_writei(pcm_handle, buf, nread)) != nread)
			{
				fprintf(stderr,"Failed to write audio %s", snd_strerror(err));
				snd_pcm_prepare(pcm_handle);
			}
		}
	}
	snd_pcm_drain(pcm_handle);
	snd_pcm_close(pcm_handle);
	
	return 0;
}