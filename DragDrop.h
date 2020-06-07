#include "stdafx.h"

class CDragDrop : public IDropTarget  
{
public:
	CDragDrop();
	virtual ~CDragDrop();

	// Interface IDropTarget
	HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState, POINTL pt, DWORD *pdwEffect);
	HRESULT STDMETHODCALLTYPE DragEnter(IDataObject * pDataObject, DWORD grfKeyState, POINTL pt, DWORD * pdwEffect);
	HRESULT STDMETHODCALLTYPE DragLeave(void);
	HRESULT STDMETHODCALLTYPE Drop(IDataObject *pDataObj, DWORD grfKeyState, POINTL pt, DWORD __RPC_FAR *pdwEffect);
	virtual void ProcessData(CString Data)=0;

	// Interface IUnknown	
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);
	ULONG STDMETHODCALLTYPE AddRef(void);
	ULONG STDMETHODCALLTYPE Release(void);
	ULONG tb_RefCount;
	CFile *tb_pDragFile;
};
