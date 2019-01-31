//Create by lsxk@hsbbs 2007/8/20
//人来修改，新增随机数，vip年月终身 概率等因素

/*
使用方法介绍：
1、主程序调用。符合条件则返回1，否则返回0.
QUEST_D->questing(人物,难度调整系数,四维,在线人数限制)

2、特殊玩家设定:
总共两种特殊玩家：
deny_quest_player----只要在这个组里的id,返回的值就是0,不进行任
何判断。
vip_quest_player 该组不开放

两种方式设定：
A:在/adm/daemons/questd.c里，的vip_quest_player数组里加上player
的id, 或者deny_quest_player数组里加上id. update更新即可永久生效.
B:用函数调用添加：
QUEST_D->add_quest_player(人物，"DENY")--将人物临时添加到deny组里
QUEST_D->add_quest_player(人物，"VIP")---将人物临时添加到vip组里
QUEST_D->delete_quest_player(人物，"DENY")--将人物临时从deny组里删除
QUEST_D->delete_quest_player(人物，"VIP")--将人物临时从vip组里删除
*/

#include <ansi.h>

//拒绝解quest玩家列表，惩罚恶意捣乱的人。
string *deny_quest_player = ({ });

//解密标志
int setquestmark(object me,string questname,int mark);
//解密时间
int setquesttime(object me,string questname);

int queryquest(object me,string questname);

int queryquesttime(object me,string questname);

int queryquestfail(object me,string questname);

string *deny_quest_player = ({"zmud",});

//以下列表中的player将提高一定解quest成功率，几率由传递的参数决定。
string *vip_quest_player = ({"zmud", });

//添加该player到相应的数组中。由arg控制到deny还是vip.
void add_quest_player(object ob, string arg)
{
    int i;
    if(arg=="DENY"){
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(ob->query("id")==deny_quest_player[i])
                return;

        deny_quest_player += ({ob->query("id")});
    }
    else{
        for(i=0;i<sizeof(vip_quest_player);i++)
            if(ob->query("id")==vip_quest_player[i])
                return;

        vip_quest_player += ({ob->query("id")});
    }
    return;
}

//从数组中删除该player。由arg控制到deny还是vip.
void delete_quest_player(object ob, string arg)
{
    if(arg=="DENY"){
        deny_quest_player -= ({ob->query("id")});
    }
    else{
        vip_quest_player -= ({ob->query("id")});
    }
    return;
}


//外部调用接口  //questing(ob,1000,120,1,"jiuyang")
//quest在线人数设置为0，是不限制

//绝世quest的判断
int questing(object me,int probability,int property,int maxuser,string questname)
{
    int i, mboth,total,oldtotal, j,vip,hidep =0;
	object* ppl;
	string fullquestname;
	
	fullquestname="quest/"+questname+"/pass";
	    //黑名单永不开
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(me->query("id")==deny_quest_player[i])
                return 0;
			
    if(!objectp(me)) return 0;
	if (queryquesttime(me,questname)) return 0;//时间不到直接失败
	if (queryquest(me,questname)) return 1;//解开了就不判断了

	
	//如果是0，则不限制
	if (maxuser >0 )
	{
		ppl = users();
		i = sizeof(ppl);
	     while(i--) {
		if (userp(ppl[i]) && !wizardp(ppl[i]) && ppl[i]->query(fullquestname))
		j++;
	   }    
	}
	else
		j=-1;//在线上限等于不限制
   //判断vip
    //判断vip
     vip=random(25);
    if (me->query("buyvip")) vip =random(17);
	if (me->query("y-card-vip")) vip =random(20);
	if (me->query("m-card-vip")) vip =random(22);      
   
	   hidep=random(me->query("kar")); 
   	   
    probability=random(probability);
   oldtotal =me->query("str")+ me->query("int")+ me->query("dex")+ me->query("con"); 
   total=random(oldtotal);
   
    //write("\n"+me->query("name")+"人品概率："+probability+"quest在线人数："+j+"vip概率："+vip+"富源："+hidep+"四维："+total+"\n");
	   if ((probability==0) &&  //真人人品随机数概率
	        (vip==3) &&       //vip概率
			(hidep>28) &&  //隐藏天赋条件
			(total>property)  &&//四维条件				
			(j<maxuser) //在线quest人数限制
		   )
		   {
			   //这里统一记录时间和标记
			   setquestmark(me,questname,1);
			   //统一记录日志
 log_file("quest/"+questname+"_log",sprintf("%-18s失败%s次后，成功解开%s，福<大于28>：%d(%d)  人品<等于0>：%d vip人品<等于3>：%d 四维<大于%d>：%d(%d)  。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,property,total,oldtotal), me);
		       return 1;	  
		   }
		   else
		   {
			  setquestmark(me,questname,0);
log_file("quest/"+questname+"_log",sprintf("%-18s失败%s次后，未能解开%s，福<大于28>：%d(%d)  人品<等于0>：%d vip人品<等于3>：%d 四维<大于%d>：%d(%d) 。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,property,total,oldtotal), me);
			
		   }
    return 0;
}


//普通quest，不判断四维, 用probability来控制难度，数字越大越难
int easy_questing(object me,int probability,string questname)
{
    int i, j,vip,hidep =0;	
	string fullquestname;	
	fullquestname="quest/"+questname+"/pass";
	    //黑名单永不开
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(me->query("id")==deny_quest_player[i])
                return 0;
			
    if(!objectp(me)) return 0;
	
	if (queryquesttime(me,questname)) return 0;//时间不到直接失败
	
	if (queryquest(me,questname)) return 1;//解开了就不判断了
	
   //判断vip
     vip=random(25);
    if (me->query("buyvip")) vip =random(10);
	if (me->query("y-card-vip")) vip =random(15);
	if (me->query("m-card-vip")) vip =random(20);       
   
	  hidep=random(me->query("kar")); 
	  probability=random(probability);
   
     if ((probability==0) &&  //真人人品随机数概率
	        (vip<=3) &&       //vip概率
			(hidep>=20) //隐藏天赋条件			
		   )
		   {
			   //这里统一记录时间和标记
			   setquestmark(me,questname,1);
			   //统一记录日志
   log_file("quest/"+questname+"_log",sprintf("%-18s失败%s次后，成功解开%s，福<大于20>：%d(%d)  人品<等于0>：%d vip人品<小于等于3>：%d 。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip), me);
		       return 1;	  
		   }
		   else
		   {
			   setquestmark(me,questname,0);
			  log_file("quest/"+questname+"_log",sprintf("%-18s失败%s次后，未能解开%s，福<大于20>：%d(%d)  人品<等于0>：%d vip人品<小于等于3>：%d 。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip), me);			
		   }  
    return 0;
}

//job次数相关的quest
//如果没job2，就job2 name任意 次数写-1
//标记有两种， 临时性的和永久性的,若jobtempmark非空格，则是临时标记
int job_questing(object me,int probability,string questname,string job1,int job1num,string job2,int job2num,string jobtempmark)
{	
	
	int i, j,vip,hidep,totaljob =0;	
	string fullquestname;	
	fullquestname="quest/"+questname+"/pass";
	    //黑名单永不开
        for(i=0;i<sizeof(deny_quest_player);i++)
            if(me->query("id")==deny_quest_player[i])
                return 0;			
    if(!objectp(me)) return 0;
	if (queryquest(me,questname)) return 1;//解开了就不判断了
	
	
   //判断vip
     vip=random(25);
    if (me->query("buyvip")) vip =random(10);
	if (me->query("y-card-vip")) vip =random(15);
	if (me->query("m-card-vip")) vip =random(20);       
   
	  hidep=random(me->query("kar")); 
	  probability=random(probability);
	  
	  //获取job次数
	 totaljob=me->query("job_time/"+job1)+me->query("job_time/"+job2);	  
   
     if ((probability==0) &&  //真人人品随机数概率
	        (vip<=3) &&       //vip概率
			(hidep>=20) && //隐藏天赋条件			
			(random(me->query("job_time/"+job1))>job1num) &&  //job1次数
			(random(me->query("job_time/"+job2))>job2num) && //job1次数
			(totaljob % 50 == 0) //整除50
		   )
		   {
			   
			   //判断是临时标记还是永久 
			   
			   if (jobtempmark =="")
			   //这里统一记录时间和标记
			   {
				  setquestmark(me,questname,1);			   
				   
			   //统一记录日志
   log_file("quest/"+questname+"_log",sprintf("%-18s失败%s次后，成功解开%s，福<大于20>：%d(%d)  人品<等于0>：%d vip人品<小于等于3>：%d job1%s：%d job2%s：%d 。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);
			   }
			   else
			   {			   
						 me->set_temp(jobtempmark,1);			   
			   log_file("quest/"+questname+"_log",sprintf("%-18s成功解开%s，福<大于20>：%d(%d)  人品<等于0>：%d vip人品<小于等于3>：%d job1%s：%d job2%s：%d 。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",jobtempmark,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);
			   }
		       return 1;	  
		   }
		   else
		   {
			    if (jobtempmark =="")  {
					setquestmark(me,questname,0);				
			log_file("quest/"+questname+"_log",sprintf("%-18s失败%s次后，未能解开%s，福<大于20>：%d(%d)  人品<等于0>：%d vip人品<小于等于3>：%d job1%s：%d job2%s：%d 。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",chinese_number(queryquestfail(me,questname)),questname,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);					
				}					
				else { 
				me->delete_temp(jobtempmark,0);
					log_file("quest/"+questname+"_log",sprintf("%-18s未能解开%s，福<大于20>：%d(%d)  人品<等于0>：%d vip人品<小于等于3>：%d job1%s：%d job2%s：%d 。\n",
              			me->name(1)+"("+capitalize(getuid(me))+")",jobtempmark,
              			hidep,me->query("kar"),probability,vip,job1,me->query("job_time/"+job1),job2,me->query("job_time/"+job2)), me);				
					
				}
		   }  
    return 0;	
}





//设置quest标记 1为成功，0为失败
int setquestmark(object me,string questname,int mark)
{
	if(!objectp(me)) return 0;
	if (mark==0)
      me->add("quest/"+questname+"/fail",1);		
  else 
	  me->set("quest/"+questname+"/pass", mark);
 //记录时间  
  setquesttime(me,questname);
   return 1;
}

//返回quest标记
int queryquest(object me,string questname)
{
	return me->query("quest/"+questname+"/pass");
}

//返回失败次数
int queryquestfail(object me,string questname)
{
	return me->query("quest/"+questname+"/fail");
}

int setmytitle(object me,string etitle,string ctitle)
{
	 if(!objectp(me)) return 0;	 
	 me->set("title",ctitle);
	 me->set("mytitle/quest/"+etitle,ctitle);
	 return 1;
}
int setquesttime(object me,string questname)
{
     if(!objectp(me)) return 0;	
	 me->set("quest/"+questname+"/time",time());
	 return 1;
}
int queryquesttime(object me,string questname)
{
	int time;
     if(!objectp(me)) return 1;	
	 if (!me->query("quest/"+questname+"/time")) return 0;			
	
	  time=time() - me->query("quest/"+questname+"/time");
	  if (time > 86400) return 0;
	  return 1;	 
}
