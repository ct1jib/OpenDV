/*
 *   Copyright (C) 2015 by Jonathan Naylor G4KLX
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "Thread.h"

#if defined(WIN32)

CThread::CThread() :
m_handle()
{
}

CThread::~CThread()
{
}

bool CThread::run()
{
  m_handle = ::CreateThread(NULL, 0, &helper, this, 0, NULL);

  return m_handle != NULL;
}


void CThread::wait()
{
  ::WaitForSingleObject(m_handle, INFINITE);

  ::CloseHandle(m_handle);
}


DWORD CThread::helper(LPVOID arg)
{
  CThread* p = (CThread*)arg;

  p->entry();

  return 0UL;
}

void CThread::sleep(unsigned int s)
{
	::Sleep(s * 1000U);
}

void CThread::milliSleep(unsigned int ms)
{
	::Sleep(ms);
}

#else

CThread::CThread() :
m_thread()
{
}

CThread::~CThread()
{
}

bool CThread::run()
{
  return ::pthread_create(&m_thread, NULL, helper, this) == 0;
}


void CThread::wait()
{
  ::pthread_join(m_thread, NULL);
}


void* CThread::helper(void* arg)
{
  CThread* p = (CThread*)arg;

  p->entry();

  return NULL;
}

void CThread::sleep(unsigned int s)
{
	::sleep(s);
}

void CThread::milliSleep(unsigned int ms)
{
	::usleep(ms * 1000U);
}

#endif