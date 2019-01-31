// rebuild for gmd job
// by renlai

#include <ansi.h>

#define JOB_NPC "/u/anger/fbnpc/mingjiao-jiaozhong"
#define JOB_PLACE "/d/mingjiao/gmd"


private void give_raward(object me);

int update_condition(object me, int duration)
{
	//object *lineup;
	object *team;
	object *ob;
	//object *ob;
	object fbroom;
	string party;
	string npcname;
	int lvl,index,i,j,guan;

	fbroom=me->query_temp("fbroom");
	
	ob = all_inventory(environment(me));
	
	//防止在副本里解除退伍作弊
	if (me->query_temp("gmd_job/team"))
	{
	    if (me->query_temp("gmd_job/team") !=me->query_team())	
	    {
		    write(HIY "你组队出现问题，任务失败。\n" NOR);
		    me->set_temp("gmdfail",1);
	    }
	}
	
	if (me->query_temp("gmdfail"))
	{
		 //销毁副本空间 
		write(HIY "你力不从心，任务失败。\n" NOR);
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
				 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行围攻光明顶失败！\n"NOR);
				       			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
			
			if (living(team[index])) team[index]->move(JOB_PLACE);				
				team[index]->delete_temp("gmdfail");
				team[index]->delete_temp("gmd_job");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("gmd_busy",70);
			}   
			}
           else {
			   CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")围攻光明顶失败！\n"NOR);	
			  if (living(me))  me->move(JOB_PLACE);
			   me->delete_temp("gmdfail");
			   me->delete_temp("gmd_job");
			   me->apply_condition("job_busy",10);
		       me->apply_condition("gmd_busy",70);
		   }   
           
			destruct(fbroom);
		}
		log_file( "job/gmd", sprintf("%8s%-10s围攻光明顶任务，人员伤亡导致离开副本失败，经验：%d。",
		   me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		 me->delete_temp("gmdfail");
		 me->delete_temp("gmd_job");
		 me->apply_condition("job_busy",10);
		 me->apply_condition("gmd_busy",70);
		return 0;
		
	}
	
	//判断长时间在副本发呆就失败
	
	if(duration==100)
	{
		write(HIY "你用时太久，任务失败。\n" NOR);
		me->set_temp("gmdfail",1);
	}
	
	
	if( duration >= 5
	 && environment(me) == fbroom 
	 && !me->query_temp("gmd_job/enter") ){
	 	///开始	 	
		me->set_temp("gmd_job/enter",1);
		me->set_temp("gmd_job/time",random(8));
	}
	
	
	if( duration == me->query_temp("gmd_job/time")){
		if(!me->query_team()){
			lvl = me->query("max_pot");
		}
		else {
			//lineup = me->query_lineup();
			
			team = me->query_team();
			me->set_temp("gmd_job/team",team);//记录队伍
			
			lvl = 0;
			for(index=0;index<sizeof(team);index++){
				if( team[index]->query("max_pot") > lvl )
				lvl = team[index]->query("max_pot");
			}
			
		}
		me->set_temp("gmd_job/lvl", lvl-120-random(10) );
		me->set_temp("gmd_job/num",sizeof( team ) ); //记录队伍人数
	}
	
	//时间到了，而还没进入万安寺副本
	if( duration < 5
	 && !me->query_temp("gmd_job/enter") ){
		 //销毁副本空间 
		if (fbroom) 
		{
			
			team = me->query_team();
           	if (team) {		
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				team[index]->move(JOB_PLACE);
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("gmd_busy",70);
			}           
			}
			 else me->move(JOB_PLACE);
			destruct(fbroom);
		}
		tell_object(me,HIY "你赶到光明顶为时已晚，光明顶下各路已经被封锁，任务失败。\n" NOR);
		log_file( "job/gmd", sprintf("%8s%-10s围攻光明顶任务，速度太慢失败，经验：%d。",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("gmd_job");
		me->apply_condition("gmd_job",-1);
		me->apply_condition("job_busy",10);
		me->apply_condition("gmd_busy",70);
		return 0;
	}		
	
	//&& !me->query_temp("gmd_job")
	//战斗时间太久
	if( duration <= 1){
		write(HIY "你用时太久，打草惊蛇导致任务失败。\n" NOR);
		
		//销毁副本空间 
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team)
			{
           			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				team[index]->move(JOB_PLACE);
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("gmd_busy",70);
			}
			}
            
			 destruct(fbroom);
		}
		else {
			me->apply_condition("job_busy",10);
		    me->apply_condition("gmd_busy",70);
			me->move(JOB_PLACE);
		}
		log_file("job/gmd", sprintf("%8s%-10s围攻光明顶任务，时间不够失败，经验：%d。",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
	
	
	
	if( me->query_temp("gmd_job/enter") && environment(me) != fbroom) {
		 
	 	if( !present( "mingjiao jiaozhong", environment(me)) && me->query_temp("gmd_job/finish") )
	 	{
			
			//先奖励
		    give_raward(me);
			
	
	 		
			return 0;
	 	}
	 	
		tell_object(me,HIY "你擅离职守，任务失败。\n" NOR);
	    //销毁副本空间 
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
						
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				team[index]->move(JOB_PLACE);
				team[index]->apply_condition("job_busy", 120);
			}   
			}
           else me->move(JOB_PLACE);			

			destruct(fbroom);
		}
		log_file( "job/gmd", sprintf("%8s%-10s围攻光明顶任务，离开失败，经验：%d。",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("gmd_job");
		me->delete_temp("fbroom");
		me->apply_condition("gmd_job",-1);
		me->apply_condition("job_busy", 120);
		return 0;
	}
	
	if(
		me->query_temp("gmd_job/finish") >= 1000//更新成1000层 by renlai
	 ///无具体实际限制 可以放大到9 .... and more
		&& environment(me) == me->query_temp("fbroom")){
		if( present( "mingjiao jiaozhong", environment(me) ) )
		return 1;	
	  
	    give_raward(me);
	   
		
		return 0;
	}
	
	
	
	/*
	每间隔1 c 来一批 (恢复到5c)				
	5 c 进入准备状态
	*/
	if(environment(me) == fbroom && me->query_temp("gmd_job") ){
		object npc;	 
				 
		fbroom=environment(me);		
		switch (duration){	
		    case 10:				
				message_vision(CYN "你一路晓行夜宿直奔光明顶而去。\n" NOR, me);
                 break;		
            case 7:				
				message_vision(CYN "你一路行来，发现不少六派中的高手都在往光明顶处集结。\n" NOR, me);
                 break;				
			case 6:				
				message_vision(CYN "光明顶上不时飘来兵刃碰撞，拳脚击打之声，似乎有人正在打斗。\n" NOR, me);
                 break;				
			case 5:
				message_vision(BLU "又不时传来惨叫，不知是否为光明顶上明教教众所发出。\n" NOR, me);
				break;
			case 3:	
				message_vision(BLU "你站在光明顶处，准备迎战光明顶群雄轮战第"+CHINESE_D->chinese_number(me->query_temp("gmd_job/finish")+1)+"关。\n" NOR, me);					
				if ((random(me->query_temp("gmd_job/finish"))>12) && !me->query_temp("gmd_quest/save") && me->query("kar")>21 && !QUEST_D->queryquest(me,"gmd/save"))
				 {				
                      party= me->query("family/family_name");
					  npcname="成昆";
					  
					  switch (party)
					  {
						  case "丐帮": npcname="阿大" ; break;
                	      case "少林派": npcname="西域空相大师"; break;
                	      case "华山派": npcname="鲜于通"; break;					 				  
					  }
					  me->set_temp("gmd_quest/save",npcname);//救人标记
					  message_vision(BLU "忽然发现光明顶某处出现一个暗道，里面竟钻出一人,仔细一看却正是"+npcname+"，$N急忙悄声道：‘你速速去找郡主。’\n" NOR, me);	
				 }					
                 //打扫卫生
				for( i=0; i < sizeof(ob); i++ )
	               {
                       // || 					   
		               if (ob[i]->is_corpse() ||!ob[i]->is_character()) {
					       destruct(ob[i]);					      
				         }
     			   }
                fbroom->set("short", HIY"光明顶激斗第"+CHINESE_D->chinese_number(me->query_temp("gmd_job/finish")+1)+"轮-副本"NOR);
				break;						
			case 2:					
				message_vision(RED" 突然之间，从明教人群中，有几人手执兵刃来到了你的面前。\n"NOR, me);
				
 				 me->add_temp("gmd_job/finish",1);				 
		        //guan= me->query_temp("gmd_job/finish");
				npc = new(JOB_NPC);
                npc->set("targat",me);				
				npc->move(environment(me));
				
				npc = new(JOB_NPC);
				npc->set("targat",me);
				npc->move(environment(me));
				
				
				me->delete_temp("gmd_up");//允许上楼
				
				if (me->query_temp("gmd_job/finish")>10)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}
				
				if (me->query_temp("gmd_job/finish")>40)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}
				if (me->query_temp("gmd_job/finish")>60)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}				
								
				//lineup = me->query_lineup();
				team = me->query_team();
				if(team)
				{
					index=sizeof(team);
					for(index=0;index<sizeof(team);index++)
					{
						if(index<2) continue;
						npc = new(JOB_NPC);
						npc->set("targat",me);
						npc->move(environment(me));						
					}
				}
					
				
				
				 break;
		}
	}
		
	me->apply_condition("gmd_job", duration-1);
	
	if(duration==2)
	{
		me->apply_condition("gmd_job", 900);
		if (wizardp(me)) 
			tell_object(me,HIR "重新置900。\n" NOR);
		message("wizard", HIG"重新置900。\n"NOR, environment(me), me);
	}
	
	if (wizardp(me))
		tell_object(me,HIR "调试计时："+duration+"。\n" NOR);
	   message("wizard", HIG"调试计时："+duration+"。\n"NOR, environment(me), me);
	
	return 1;
}

private void give_raward(object me)
{
	//object* lineup;
	object *team;
	object fbroom;
	int i,j,k,x,y,count,finish;
	mapping *notes;
	mapping note;
	string file;
	string party;
	string npcname;
	int gmdscore;
		
	if(!me) return;
			
	
	 team = me->query_temp("gmd_job/team");//防止作弊
	 //team = me->query_team();
	 fbroom = me->query_temp("fbroom");
		
	j = me->query_temp("gmd_job/finish");
    finish=me->query_temp("gmd_job/finish");
	if (me->query("relife/times"))
	{
		x=j+random(1+j);
	}else x=random(j+1);
	
	x=(int)x/4;
	
   //保留最高记录
    if (finish>me->query("gmd_job/level")) me->set("gmd_job/level",finish);    

    note=allocate_mapping(4);
    note["player"]=	me->name(1)+"("+capitalize(getuid(me))+")";
	note["playerid"]=capitalize(getuid(me));
	note["gmdlevel"]=finish;
	note["gmdexp"]=me->query("combat_exp");

	if (file_size("/log/gmdtop") > 0) 
	{	
	   file = read_file("/log/gmdtop");	
	   notes=restore_variable(file);
	}
 
   if ( !pointerp(notes) || !sizeof(notes))
	{
		 notes = ({ note });
		 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "破光明顶第"+CHINESE_D->chinese_number(finish)+"关成功，成为光明顶破关记录保持者！\n"NOR);
		 me->set_temp("title", MAG"光明顶"+HIC"剃刀"NOR);
	}
    else
	{
		for(k = 0;k<sizeof(notes);k++) {
			if (finish>notes[k]["gmdlevel"]) {
				
				notes[k]["gmdlevel"]=finish; 
                notes[k]["gmdexp"]=me->query("combat_exp");
               	me->set_temp("title", MAG"光明顶"+HIC"剃刀"NOR);	
				
			 if (notes[k]["playerid"]==capitalize(getuid(me)))
				 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "破光明顶第"+CHINESE_D->chinese_number(finish)+"关成功，成为光明顶破关记录保持者！\n"NOR);
				 else
				 {					 
					 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "破光明顶第"+CHINESE_D->chinese_number(finish)+"层成功，超过了"+ notes[k]["player"] + "成为光明顶破关记录保持者！\n"NOR);
					 
					 notes[k]["playerid"]=capitalize(getuid(me));
                     notes[k]["player"]=me->name(1)+"("+capitalize(getuid(me))+")";	
				 }
				 				
                break;				
			}			
		}
	}	
	
	write_file("/log/gmdtop",save_variable(notes),1);
	/*
	  if (finish>=1000) {
		  //能上1000层的，有没有九阴也无所谓了。grin
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺"+CHINESE_D->chinese_number(finish)+"层成功，奖励九阴真经上册一部！\n"NOR);		
	  }	  
	*/
	  
	 if (finish>=50)
	 {
		 int type = random(2)+1;
		 object kuangshi;
		 switch(type){
				case 1:kuangshi = new("/d/zhiye/obj/kuangshi");break;
				case 2:kuangshi = new("/d/zhiye/obj/buliao");break;
				default:break;
				}
		if(kuangshi){
			kuangshi->set_level(10);
			kuangshi->set("owner",getuid(me));
			kuangshi->move(me);
			tell_object(me,"出得塔来，忽见成昆迎面走来，偷偷塞给你一件事物。\n");
		}		 
	 }
	  
	  
		 
	 me->delete_temp("gmd_up");//允许上楼
	if( !team ){
       //单人		
		me->apply_condition("job_busy",10);
		me->apply_condition("gmd_busy",60);
		me->delete_temp("gmd_job");		
		me->clear_condition("gmd_job");
		me->set("job_name", "围攻光明顶");
		
          if(j > 1 && j <= 10 )
			  TASKREWARD_D->get_reward(me,"围攻光明顶",-1,1,x,0,1,j-1,500);             
          else if(j == 1)
			 TASKREWARD_D->get_reward(me,"围攻光明顶",-1,1,x,0,1,1,160);             
          else if(j>20 && j<=30)
			  TASKREWARD_D->get_reward(me,"围攻光明顶",-1,1,x,0,3,j,4000);
		  else if(j>30 && j<=40) 
			 TASKREWARD_D->get_reward(me,"围攻光明顶",-1,1,x,0,4,j+1,6000);
		  else if(j>40 && j<=50) 
			TASKREWARD_D->get_reward(me,"围攻光明顶",-1,1,x,0,5,j+1,8000);
		  else if(j>50) 
			TASKREWARD_D->get_reward(me,"围攻光明顶",-1,1,x,0,5,j+1,10000);            
		  else TASKREWARD_D->get_reward(me,"围攻光明顶",-1,1,x,0,2,j,800);
		  

		  if( me->query_condition("fx_busy") > 50 )
			me->apply_condition("fx_busy",50);
		 
		 //加入gmd积分
		 gmdscore=0;
            if (finish>10 && finish<=20)
			{
			    gmdscore=1;	
			}
			else if (finish>20)
			{
				gmdscore=finish;;
			}
			
			
		 if (finish>10) {		   
			me->add("gmd_job/gmdscore",gmdscore);
			tell_object(me,HIY "因为围攻光明顶成功，你获得了"+CHINESE_D->chinese_number(gmdscore)+"点光明顶积分。\n" NOR);
		 }	
	

      if (environment(me) == fbroom) {				
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);
			    me->move(JOB_PLACE);
			}	 
	
			
		if (fbroom) 
		{			
			destruct(fbroom);
		}
	}
	else{
		//组队
		//sizeof(team)
		//write("现在是组队副本任务奖励，若你是组队模式,但是队员无奖励，请保存完整job日志并联系wiz。\n");
				
		   gmdscore=0;
            if (finish>10 && finish<=20)
			{
			    gmdscore=1;	
			}
			else if (finish>20)
			{
				gmdscore=finish;
			}
					 		
		
		for(i = 0;i<sizeof(team);i++){
			if(objectp(team[i]) && userp(team[i])) {
				write("队员信息:"+team[i]->query("name")+"\n");
					team[i]->apply_condition("job_busy", 10);
					team[i]->apply_condition("gmd_busy",60);
					team[i]->delete_temp("gmd_job");
					team[i]->clear_condition("gmd_job");
					team[i]->set("job_name", "围攻光明顶");
					if (team[i]->query("relife/times"))
					{
						y=j+random(1+j);
					}
					else y=random(j+1);
					
					y=(int)y/4;	

                                  if(j > 1 && j <= 10 )
									  TASKREWARD_D->get_reward(team[i],"围攻光明顶",-1,1,y,0,1,j-1,500);
                                     
                                  else if(j == 1)
									  TASKREWARD_D->get_reward(team[i],"围攻光明顶",-1,1,y,0,1,1,160);
                                   else if(j>20 && j<=30) 
									   TASKREWARD_D->get_reward(team[i],"围攻光明顶",-1,1,y,0,3,j+1,4000);
								   else if(j>30 && j<=40) 
									   TASKREWARD_D->get_reward(team[i],"围攻光明顶",-1,1,y,0,4,j+1,6000);
								   else if(j>40 && j<=50) 
									   TASKREWARD_D->get_reward(team[i],"围攻光明顶",-1,1,y,0,5,j+1,8000);
								   else if(j>50) 
									   TASKREWARD_D->get_reward(team[i],"围攻光明顶",-1,1,y,0,5,j+1,10000);
                                  else
									 TASKREWARD_D->get_reward(team[i],"围攻光明顶",-1,1,y,0,2,j,1000);
                                    

					if( team[i]->query_condition("fx_busy") > 50 )
						team[i]->apply_condition("fx_busy",30+random(20));
					
	
					if (environment(team[i]) == fbroom) {				
				         message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[i]);
				         team[i]->move(JOB_PLACE);
				}					
					
				}
				if (finish>10) {
				team[i]->add("gmd_job/gmdscore",gmdscore);
				tell_object(team[i],HIY "因为围攻光明顶成功，你获得了"+CHINESE_D->chinese_number(gmdscore)+"点光明顶积分。\n" NOR);
			    
				}
				
			}		
		if (fbroom) 
		{			
			destruct(fbroom);
		}
		}
		
		
		  
	  	//这里加quest判断
	//20层以上才有机会
	//必须加奖励后，否则job次数不对	
	//玄冥
	if (finish>19 && random(finish)>20) 
	{
		CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "破光明顶成功，并击败光明顶五散人！\n"NOR);
		
		me->set("quest/倚天屠龙记/xuanmingshenzhang/combat_exp",me->query("combat_exp"));
	    if(QUEST_D->job_questing(me,4,"倚天屠龙记/xuanming","围攻光明顶",5000,"不计算",-1,""))
	      {
			  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "因扑灭光明顶圣火成功，并得到赵敏郡主的青睐！\n"NOR);
			  message_vision(CYN "忽然从$N耳边传来声音，却是赵敏用传音入秘方式告知$N一个秘密。\n" NOR, me);
              QUEST_D->setmytitle(me,"gmdtitle",HIY"光明顶第一人"NOR);					  
	      }  
	}	
	//幻阴指法
	 else if (me->query_temp("gmd_quest/save"))
	{
		//CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "破光明顶成功，有幸救得"+me->query_temp("gmd_quest/save")+"！\n"NOR);
	    if (QUEST_D->job_questing(me,3,"gmd/save","围攻光明顶",1000,"不计算",-1,""))
		{
			QUEST_D->setmytitle(me,"gmdtitle",HIY"光明顶灭火人"NOR);
			CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "因灭圣火有功，并得到"+me->query_temp("gmd_quest/save")+"青睐！\n"NOR);
			 message_vision(CYN "忽见"+me->query_temp("gmd_quest/save")+"把$N拉过一旁，在$N耳边说了什么，$N似乎兴奋不已。\n" NOR, me);
		}
		else CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "灭圣火成功，可惜机缘未到，未得"+me->query_temp("gmd_quest/save")+"青睐！\n"NOR);
        me->delete_temp("gmd_quest/save");		
	}	
	
	else if (finish<15) CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "刺探光明顶获取到了一些情报！\n"NOR);	
    else
        CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯光明顶成功，可惜并未救得关键之人，失去了一次机缘！\n"NOR);
	
		
    me->delete_temp("fbroom");
	me->delete_temp("gmd_job");
	me->clear_condition("gmd_job");//防止Bug
}
