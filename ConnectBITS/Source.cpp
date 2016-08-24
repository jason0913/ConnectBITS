#define UNICODE
#define _WIN32_WINNT  0x0500
#include <windows.h>
#include <string>
#include "bits.h"

//Global variable that several of the code examples in this document reference.
IBackgroundCopyManager* g_pbcm = NULL;
HRESULT hr;
GUID JobId;
IBackgroundCopyJob* pJob = NULL;

int main()
{
	//Specify the appropriate COM threading model for your application.
	hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(__uuidof(BackgroundCopyManager), NULL,
			CLSCTX_LOCAL_SERVER,
			__uuidof(IBackgroundCopyManager),
			(void**)&g_pbcm);
		if (SUCCEEDED(hr))
		{
			//Use g_pbcm to create, enumerate, or retrieve jobs from the queue.
			wprintf(L"ConCreateInstance success!\n");
			//To create an upload job, replace BG_JOB_TYPE_DOWNLOAD with 
			//BG_JOB_TYPE_UPLOAD or BG_JOB_TYPE_UPLOAD_REPLY.
			hr = g_pbcm->CreateJob(L"MyDownloadJob2", BG_JOB_TYPE_DOWNLOAD, &JobId, &pJob);
			if (SUCCEEDED(hr))
			{
				//Save the JobId for later reference. 
				//Modify the job's property values.
				//Add files to the job.
				//Activate (resume) the job in the transfer queue.
				wprintf(L"CreateJob success!\n");
			}

			//Replace parameters with variables that contain valid paths.
			hr = pJob->AddFile(L"https://download.sublimetext.com/Sublime%20Text%20Build%203114%20Setup.exe", L"d:\\sbFile.exe");
			if (SUCCEEDED(hr))
			{
				//Do something.
				wprintf(L"AddFile success!\n");
			}
			hr = pJob->Resume();
			if (SUCCEEDED(hr))
			{
				wprintf(L"Activates a new job or restarts a job success!\n");
			}
			Sleep(1000 *60);
			hr = pJob->Complete();
			if (SUCCEEDED(hr))
			{
				wprintf(L"job Complete success!\n");
			}
		}
	}
	getchar();

	return 0;
}