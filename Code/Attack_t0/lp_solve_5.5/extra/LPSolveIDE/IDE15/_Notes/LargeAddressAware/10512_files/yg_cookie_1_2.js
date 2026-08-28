function yg_cookie(){
	var dc=document,a=[],c=[];
	if(dc.cookie.length>0){
		a=dc.cookie.split("; "),cl=a.length,ca=[];
		for(var i=cl-1;i>=0;i--){ca=a[i].split("=");c[ca[0]]=ca[1]}
	}
	this.getAll=function(){return a}
	this.get=function(n){return(c[n])?unescape(c[n]):0}
	this.set=function(n,v,e,p,d,s){
		v=escape(v);var today=new Date(),nv=n+"="+v;
		var str=nv+((e)?"; expires="+e:"")+((p)?"; path="+p:"")+((d)?"; domain="+d:"")+((s)?"; secure":"");
		if((n.length>0&&v.length>0)&&(((e)&&(e>today))||(!e))&&(nv.length<4000)){dc.cookie=str;a[a.length]=nv;c[n]=v;return 1}else return 0;
	}
	this.remove=function(n,p,d){
		if(c[n]){
			dc.cookie=n+"="+((p)?"; path="+p:"")+((d)?"; domain="+d:"")+"; expires=Thu, 01-Jan-1970 00:00:01 GMT";
			for(var i=a.length-1;i>=0;i--){if(a[i].indexOf(n)!=-1)a.splice(i,1)}c[n]=null;return 1;
		}else return 0;
	}
}
