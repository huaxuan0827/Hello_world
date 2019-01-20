/*****************************************************************
 * �ļ���: SimuS_GCmd.h
 * ����: SimuService��SimuGuard֮��ͨ�������
 *****************************************************************/
#pragma  once

#ifndef WIN_PLATFORM
#include "stdafx.h"
#endif

#include <vector>
#include "SimuCommunicationDef.h"

using namespace std;

/****************************************************************
 * ö���� : S_G_CMD
 * ˵�� : SimuService��SimuGuard֮��ͨ�������ֶ���
 ****************************************************************/
typedef enum euS_G_CMD
{
	S_G_CMD_UNKNOWN						= -1 ,			/* δ֪����*/
	S_G_CMD_LOADSIMUMODEL				= 0x20000001,	/* װ�ط���ģ������ */
	S_G_CMD_LOADSIMUMODEL_RESP			= 0xA0000001,	/* װ�ط���ģ����Ӧ */
	S_G_CMD_EXECSIMUMODEL				= 0x20000002,	/* ִ�з���ģ������ */
	S_G_CMD_EXECSIMUMODEL_RESP			= 0xA0000002,	/* ִ�з���ģ����Ӧ */
	S_G_CMD_PAUSESIMUMODEL				= 0x20000003,	/* ��ͣ����ģ������ */
	S_G_CMD_PAUSESIMUMODEL_RESP			= 0xA0000003,	/* ��ͣ����ģ����Ӧ */
	S_G_CMD_RESETSIMUMODEL				= 0x20000004,	/* ���÷���ģ������ */
	S_G_CMD_RESETSIMUMODEL_RESP			= 0xA0000004,	/* ���÷���ģ����Ӧ */
	S_G_CMD_SETMODELPARAM				= 0x20000005,	/* ����ģ�Ͳ������� */
	S_G_CMD_SETMODELPARAM_RESP			= 0xA0000005,	/* ����ģ�Ͳ�����Ӧ */
	S_G_CMD_TESTEVENT_REPORT			= 0xA0000006,	/* �����¼��ϱ� */
	S_G_CMD_EXCEPTEVENT_REPORT			= 0xA0000007,	/* �쳣�ϱ� */
	S_G_CMD_COMPILESIMUMODEL			= 0x00000008,	/* ����ģ������ */
	S_G_CMD_COMPILESIMUMODEL_RESP		= 0xA0000008,	/* ����ģ����Ӧ */
	S_G_CMD_COMPILEINFO_REPORT			= 0xA0000009,	/* ������Ϣ�ϱ� */
} S_G_CMD;


/*BEGIN  SimuService��SimuGuard֮��ͨ������֡���ֶ���֡��������λ���Լ���С���� */
#define S_G_CMD_POS_VERSION				0
#define S_G_CMD_POS_FRAMELEN			4
#define S_G_CMD_POS_COMMAND				8
#define S_G_CMD_POS_FRAMEBODYLEN		12
#define S_G_CMD_POS_SIMUPROJECTID		16
#define S_G_CMD_POS_SIMUMODELID			52
#define S_G_CMD_POS_RESERVED2			56
#define S_G_CMD_POS_RESERVED3			60
#define S_G_CMD_POS_RESERVED4			64
#define S_G_CMD_POS_FRAMEBODY			80
#define S_G_CMD_HEADER_SIZE					80
#define S_G_CMD_BODY_SIZE(bodylen)			(bodylen)
#define S_G_CMD_SIZE(bodylen)				((S_G_CMD_HEADER_SIZE) + (S_G_CMD_BODY_SIZE(bodylen)))
#define S_G_CMD_SIZE_VERSION				4
#define S_G_CMD_SIZE_FRAMELEN				4
#define S_G_CMD_SIZE_COMMAND				4
#define S_G_CMD_SIZE_FRAMEBODYLEN			4
#define S_G_CMD_SIZE_SIMUPROJECTID			36
#define S_G_CMD_SIZE_SIMUMODELID			4
#define S_G_CMD_SIZE_RESERVED2				4
#define S_G_CMD_SIZE_RESERVED3				4
#define S_G_CMD_SIZE_RESERVED4				16
#define S_G_CMD_SIZE_FRAMEBODY(bodylen)		(bodylen)
/*END  SimuDisplay��SimuService֮��ͨ������֡���ֶ���֡��������λ���Լ���С���� */

/****************************************************************
 * ���� : CSimuS_GCmd
 * ���� : ��
 * ˵�� : SimuService��SimuGuard֮��ͨ�ŵ���������ĸ���
 ****************************************************************/
class CSimuS_GCmd
{
public:
	CSimuS_GCmd(S_G_CMD sgc);
	virtual ~CSimuS_GCmd();

	/* Ԥ�������� , �����Ӧ������ */
	static S_G_CMD PreParseCmd(unsigned char* szBuffer , unsigned long nBufferLen , unsigned long& nCmdDataLen);	
	
	/* ��ȡ����ֵ */
	S_G_CMD GetCmdType() const;	
	
	/* ���÷��湤��ID�� */
	void SetSimuProjectID(const unsigned char* szId);	
	
	/* ��ȡ����֡���� */
	unsigned long GetFrameLen();		
	
	/* ��ȡ����֡�峤�� */
	unsigned long GetFrameBodyLen();
	
	/* ��ȡ���湤��ID */
	void GetSimuProjectID(unsigned char* szId);
	
	/* ����ģ��ID */
	void SetSimuModelID(const unsigned char *szModelID);

	/* ��ȡģ��ID */
	void GetSimuModelID(unsigned char *szModelID);

	/* ���л�����֡ͷ */
	unsigned long SerializeHeader(unsigned char* szBuffer);	
	
	/* ���л����� */
	virtual unsigned long Serialize(unsigned char* szBuffer);
	
	/* �����л���������� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);

	/* �����ӡ */
	virtual void Print(char* szBuffer); 

protected:
	unsigned long CalcFrameLen();
	virtual unsigned long CalcFrameBodyLen() = 0;

	S_G_CMD		   m_sgc;																																													/* ������ */
	unsigned char  m_szVersion[S_G_CMD_SIZE_VERSION];																												/* ����汾�� */
	unsigned long  m_nFrameLen;																																							/* ����֡����*/
	unsigned long  m_nCmd;																																										/* ������ */
	unsigned long  m_nFrameBodyLen;																																					/* ����֡�峤�� */

	unsigned char  m_szSimuProjectID[S_G_CMD_SIZE_SIMUPROJECTID];																					/* ���湤��ID�� */
	unsigned char  m_szSimuModelID[S_G_CMD_SIZE_SIMUMODELID];																									/* ������ֶ�1 */
	unsigned char  m_szReserved2[S_G_CMD_SIZE_RESERVED2];																									/* ������ֶ�2 */
	unsigned char  m_szReserved3[S_G_CMD_SIZE_RESERVED3];																									/* ������ֶ�3 */
	unsigned char  m_szReserved4[S_G_CMD_SIZE_RESERVED4];																									/* ������ֶ�4 */
};

/****************************************************************
 * ���� : CSimuS_GLoadSimuModelCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ���ط���ģ����������
 ****************************************************************/
class CSimuS_GLoadSimuModelCmd : public CSimuS_GCmd
{
public:
	CSimuS_GLoadSimuModelCmd();
	virtual ~CSimuS_GLoadSimuModelCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer);

	void SetParam(const CommuLoadSimuModelParam_t *pParam);
	const CommuLoadSimuModelParam_t *GetParam();

protected:
	virtual unsigned long CalcFrameBodyLen();

	CommuLoadSimuModelParam_t	m_CommuParam;
};

/****************************************************************
 * ���� : CSimuS_GLoadSimuModelRespCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ���ط���ģ����Ӧ����
 ****************************************************************/
class CSimuS_GLoadSimuModelRespCmd : public CSimuS_GCmd
{
public:
	CSimuS_GLoadSimuModelRespCmd();
	virtual ~CSimuS_GLoadSimuModelRespCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetResult(unsigned long result);
	unsigned long GetResult();

	void SetErrInfo(unsigned char *szErrInfo, unsigned long nErrLen);
	int  GetErrInfo(unsigned char *szBuffer);
protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long	m_ulResult;		
	unsigned long   m_ulErrInfoLen;																																					/* ���ӽ�� */
	unsigned char   m_szErrInfo[1024];	
};

/****************************************************************
 * ���� : CSimuS_GExecSimuModelCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ִ�з���ģ��
 ****************************************************************/
class CSimuS_GExecSimuModelCmd : public CSimuS_GCmd
{
public:
	CSimuS_GExecSimuModelCmd();
	virtual ~CSimuS_GExecSimuModelCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetData(int nExecMode, int TestTask, int TestCase);
	unsigned long GetExecMode();
	unsigned long GetTestTask();
	unsigned long GetTestCase();

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long  m_nExecMode;
	unsigned long  m_nTestTask;
	unsigned long  m_nTestCase;
};

/****************************************************************
 * ���� : CSimuS_GExecSimuModelRespCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ִ�з���ģ����Ӧ����
 ****************************************************************/
class CSimuS_GExecSimuModelRespCmd : public CSimuS_GCmd
{
public:
	CSimuS_GExecSimuModelRespCmd();
	virtual ~CSimuS_GExecSimuModelRespCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetResult(unsigned long result);
	unsigned long GetResult();

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long m_ulResult;
};

/****************************************************************
 * ���� : CSimuS_GPauseSimuModelCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ��ͣ����ģ��
 ****************************************************************/
class CSimuS_GPauseSimuModelCmd : public CSimuS_GCmd
{
public:
	CSimuS_GPauseSimuModelCmd();
	virtual ~CSimuS_GPauseSimuModelCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

protected:
	virtual unsigned long CalcFrameBodyLen();

};

/****************************************************************
 * ���� : CSimuS_GPauseSimuModelRespCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ��ͣ����ģ����Ӧ����
 ****************************************************************/
class CSimuS_GPauseSimuModelRespCmd : public CSimuS_GCmd
{
public:
	CSimuS_GPauseSimuModelRespCmd();
	virtual ~CSimuS_GPauseSimuModelRespCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetResult(unsigned long result);
	unsigned long GetResult();

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long m_ulResult;
};

/****************************************************************
 * ���� : CSimuS_GResetSimuModelCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ���÷���ģ��
 ****************************************************************/
class CSimuS_GResetSimuModelCmd : public CSimuS_GCmd
{
public:
	CSimuS_GResetSimuModelCmd();
	virtual ~CSimuS_GResetSimuModelCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

protected:
	virtual unsigned long CalcFrameBodyLen();

};

/****************************************************************
 * ���� : CSimuS_GResetSimuModelRespCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ���÷���ģ����Ӧ����
 ****************************************************************/
class CSimuS_GResetSimuModelRespCmd : public CSimuS_GCmd
{
public:
	CSimuS_GResetSimuModelRespCmd();
	virtual ~CSimuS_GResetSimuModelRespCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetResult(unsigned long result);
	unsigned long GetResult();

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long m_ulResult;
};

/****************************************************************
 * ���� : CSimuS_GSetSimuModelParamCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ���÷���ģ�Ͳ���
 ****************************************************************/
class CSimuS_GSetSimuModelParamCmd : public CSimuS_GCmd
{
public:
	CSimuS_GSetSimuModelParamCmd();
	virtual ~CSimuS_GSetSimuModelParamCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetModelParam(const vector<CommuSetModelParam_t *> &vecModelParam);
	const vector<CommuSetModelParam_t *> *GetModelParam();

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long		m_nModelParamCount;
	vector<CommuSetModelParam_t*>	m_vecModelParam;
};

/****************************************************************
 * ���� : CSimuS_GSetSimuModelParamRespCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ���÷���ģ�Ͳ�����Ӧ����
 ****************************************************************/
class CSimuS_GSetSimuModelParamRespCmd : public CSimuS_GCmd
{
public:
	CSimuS_GSetSimuModelParamRespCmd();
	virtual ~CSimuS_GSetSimuModelParamRespCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetResult(unsigned long result);
	unsigned long GetResult();

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long m_ulResult;
};

/****************************************************************
 * ���� : CSimuS_GTestEventReportCmd
 * ���� : CSimuS_GCmd
 * ˵�� : �����¼��ϱ�
 ****************************************************************/
class CSimuS_GTestEventReportCmd : public CSimuS_GCmd
{
public:
	CSimuS_GTestEventReportCmd();
	virtual ~CSimuS_GTestEventReportCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetReport(const CommuTestEventReport_t *pReport);
	const CommuTestEventReport_t *GetReport();

protected:
	virtual unsigned long CalcFrameBodyLen();

	CommuTestEventReport_t	m_Report;
};

/****************************************************************
 * ���� : CSimuS_GExceptEventReportCmd
 * ���� : CSimuS_GCmd
 * ˵�� : �쳣�¼��ϱ�
 ****************************************************************/
class CSimuS_GExceptEventReportCmd : public CSimuS_GCmd
{
public:
	CSimuS_GExceptEventReportCmd();
	virtual ~CSimuS_GExceptEventReportCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);																	/* �����л���������� */
	virtual void Print(char* szBuffer); 

	void SetReport(const CommuExceptReport_t *pReport);
	const CommuExceptReport_t *GetReport();

protected:
	virtual unsigned long CalcFrameBodyLen();

	CommuExceptReport_t m_Report;
};

/****************************************************************
 * ���� : CSimuS_GCompileSimuModelCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ����ģ������
 ****************************************************************/
class CSimuS_GCompileSimuModelCmd : public CSimuS_GCmd
{
public:
	CSimuS_GCompileSimuModelCmd();
	virtual ~CSimuS_GCompileSimuModelCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);	
	virtual void Print(char* szBuffer);

	int SetCompileParam(const CommuModelCompileParam_t *pParam);
	int GetCompileParam(CommuModelCompileParam_t *pParam);
	const CommuModelCompileParam_t *GetCompileParam();

protected:
	virtual unsigned long CalcFrameBodyLen();
	CommuModelCompileParam_t m_CompileParam;
};

/****************************************************************
 * ���� : CSimuS_GCompileSimuModelRespCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ����ģ��������Ӧ
 ****************************************************************/
class CSimuS_GCompileSimuModelRespCmd : public CSimuS_GCmd
{
public:
	CSimuS_GCompileSimuModelRespCmd();
	virtual ~CSimuS_GCompileSimuModelRespCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);	
	virtual void Print(char* szBuffer);

	void SetResult(unsigned long nResult);
	unsigned long GetResult();

	void SetErrInfo(const char *szErrInfo, unsigned long ulErrLen);
	unsigned long GetErrInfo(char *pszErrInfo, unsigned long nBuffLen);

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long m_ulResult;
	unsigned long m_ulErrInfoLen;
	char m_szErrInfo[1024];
};

/****************************************************************
 * ���� : CSimuS_GCompileInfoRepCmd
 * ���� : CSimuS_GCmd
 * ˵�� : ������Ϣ�ϱ�����
 ****************************************************************/
class CSimuS_GCompileInfoRepCmd : public CSimuS_GCmd
{
public:
	CSimuS_GCompileInfoRepCmd();
	virtual ~CSimuS_GCompileInfoRepCmd();

	virtual unsigned long Serialize(unsigned char* szBuffer);																											/* ���л����� */
	virtual BOOL Unserialize(unsigned char* szBuffer , unsigned long nBufferLen);	
	virtual void Print(char* szBuffer);

	void SetCompileInfo(unsigned long ulCompileRepType, const char *szCompileInfo);
	unsigned long GetCompileInfo(unsigned long *pCompileRepType, char *pszCompileInfo, unsigned long nBuffLen);

protected:
	virtual unsigned long CalcFrameBodyLen();

	unsigned long m_ulCompileRepType;
	unsigned long m_ulRepInfoLen;
	char m_szCompileInfo[2048];
};