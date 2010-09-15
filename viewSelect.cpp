
#include <maya/MIOStream.h>
#include <maya/M3dView.h>
#include <maya/MFnCamera.h>
#include <maya/MDrawTraversal.h>
#include <maya/MDagPath.h>
#include <maya/MSimple.h>
#include <maya/MGlobal.h>
#include <maya/MPlug.h>
#include <maya/MSelectionList.h>
#include <maya/MTime.h>
#include <maya/MAnimControl.h>

#include <maya/MFnDependencyNode.h>
#include <maya/MStringArray.h>


//  unused includes
//#include <maya/MPointArray.h>
//#include <maya/MMatrix.h>
//#include <maya/MFloatMatrix.h>
//#include <maya/MFnTransform.h>

DeclareSimpleCommand( viewSelector, "rbw", "8.5");

MStatus viewSelector::doIt( const MArgList& args )

{
	MStatus stat = MS::kSuccess;
	M3dView view;
	MDagPath camera ;	
        MAnimControl mctrl;
        //MSelectionList list;       
        MDagPath foundObj;
        MTime cunit;
        MStringArray selectionS;
	//	current viewport
	M3dView activeView = view.active3dView();
	//	curren camera
	activeView.getCamera(camera);
	MFnCamera cameraFn(camera.node());
        //  get min/max frame range       
        MTime minT = mctrl.minTime();
        MTime maxT = mctrl.maxTime();              
        //  getCurrentFrame
        MTime ctime = mctrl.currentTime();
	// portH & portW
	unsigned int portH = activeView.portHeight();
	unsigned int portW = activeView.portWidth();	
        //  for every frame
        for(MTime u = minT.as(cunit.unit());u<=maxT.as(cunit.unit());u++){
            //  traverse scene from view
            MDrawTraversal trav;  
            //  set frustum for camera
            trav.setFrustum(camera,portW,portH);
            if (trav.frustumValid()){
                //  traverse scene from view
                trav.traverse();
                //  get total number of selected items
                unsigned int numObjs = trav.numberOfItems();
                //  for every object
                for(unsigned int i=0;i<numObjs;i++){
                        //  get item 
                        trav.itemPath(i,foundObj);
                        MFnDependencyNode nodeFn(foundObj.node());
                        //cout << "nodeType:" << nodeFn.typeName() << "\n" << endl;
                        //  select only meshes or..... to extend
                        if (nodeFn.typeName() == "mesh"){
                            //  get transform over the shape
                            MObject tShape = foundObj.transform();
                            //  add transform name to name list
                            MFnDependencyNode nodeTFn(tShape);
                            selectionS.append(nodeTFn.name());
                        }
                        //cout <<" found intem: "<<foundObj.partialPathName() <<" @time "<<u.as(cunit.unit()) <<"\n"<< endl;
                }
            }
        //  set current time to time u that is > mintime & <= maxtimme
        mctrl.setCurrentTime(u);
        }
        // restore current frame
        mctrl.setCurrentTime(ctime);
        //  set output 
        clearResult();
        setResult(selectionS);
	return stat;
}

/*  appunti
         
	//	projection matrix
	MFloatMatrix projMatrix	= cameraFn.projectionMatrix();
	
	//	rendering frustum
	double  aspectRatio = cameraFn.aspectRatio();
	double  left, right,bottom,top;
	cameraFn.getRenderingFrustum(aspectRatio,left,right,bottom,top);
	cout<< " aspect ratio: " << aspectRatio << "\n" <<endl;
	cout<< " rendering frustum left: " << left << " right: " << right << " top: " << top << " bottom: " << bottom << "\n" << endl;
	
	
	//	film frustum
	double  focalLength = cameraFn.focalLength();
	MPointArray clipPlanes;
	cameraFn.getFilmFrustum(focalLength,clipPlanes);
	cout << " focal length : " << focalLength << "\n" << endl;
	
	//cout << " portH: " << portH << " portW: " << portW<< "\n" << endl;

	// Hfov Vfov
	double hfov,vfov;
	cameraFn.getPortFieldOfView(portH,portW,hfov,vfov);
	cout << " hfov: " << hfov << " vfov: " << vfov<< "\n" << endl;

	// clipping planes
	double neardCp = cameraFn.nearClippingPlane();
	double farCp   = cameraFn.farClippingPlane();
	cout << " neardCp: " << neardCp << " farCp: " << farCp<< "\n" << endl;
	
	// camera dagMatrix
	MObject camT  = camera.transform();
	MFnTransform cameraTr(camT);
	MMatrix camWM = cameraTr.transformationMatrix();
	//MMatrix camWM = cameraFn.transformationMatrix();


	MMatrix viewM;
	activeView.projectionMatrix(viewM);
	      
      
        //stat=trav.setPerspFrustum(hfov,aspectRatio,neardCp,farCp,camWM);

        //stat=trav.setFrustum()
        //cout <<" stat: " << stat << endl; 
*/  
