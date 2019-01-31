// rebuild for was job
// by renlai

#include <ansi.h>

#define JOB_NPC "/d/was/npc/menggu-wushi"
#define JOB_PLACE "/d/was/was"


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
	if (me->query_temp("was_job/team"))
	{
	    if (me->query_temp("was_job/team") !=me->query_team())	
	    {
		    write(HIY "你组队出现问题，任务失败。\n" NOR);
		    me->set_temp("wasfail",1);
	    }
	}
	
	if (me->query_temp("wasfail"))
	{
		 //销毁副本空间 
		write(HIY "你力不从心，任务失败。\n" NOR);
		if (fbroom) 
		{
			
			team = me->query_team();
			if (team) {
				CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行闯万安寺解救六派失败！\n"NOR);
				       			
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				if (living(team[index])) team[index]->move(JOB_PLACE);	
				team[index]->delete_temp("wasfail");
				team[index]->delete_temp("was_job");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);	
			}   
			}
           else {
			   CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")闯万安寺解救六派失败！\n"NOR);	
			   if (living(me))  me->move(JOB_PLACE);
			   me->delete_temp("wasfail");
			   me->delete_temp("was_job");
		   }   
           
			destruct(fbroom);
		}
		log_file( "job/was", sprintf("%8s%-10s勇闯万安寺任务，人员伤亡导致离开副本失败，经验：%d。",
		   me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		 me->delete_temp("wasfail");
		 me->delete_temp("was_job");
		 me->apply_condition("job_busy",10);
		 me->apply_condition("was_busy",70);		
		return 0;
		
	}
	
	
	//判断长时间在副本发呆就失败
	
	if(duration==100)
	{
		write(HIY "你用时太久，任务失败。\n" NOR);
		me->set_temp("wasfail",1);
	}
	
	if( duration >= 5
	 && environment(me) == fbroom 
	 && !me->query_temp("was_job/enter") ){
	 	///开始	 	
		me->set_temp("was_job/enter",1);
		me->set_temp("was_job/time",random(8));
	}
	
	
	if( duration == me->query_temp("was_job/time")){
		if(!me->query_team()){
			lvl = me->query("max_pot");
		}
		else {
			//lineup = me->query_lineup();
			
			team = me->query_team();
			me->set_temp("was_job/team",team);//记录队伍
			
			lvl = 0;
			for(index=0;index<sizeof(team);index++){
				if( team[index]->query("max_pot") > lvl )
				lvl = team[index]->query("max_pot");
			}
			
		}
		me->set_temp("was_job/lvl", lvl-120-random(10) );
		me->set_temp("was_job/num",sizeof( team ) ); //记录队伍人数
	}
	
	//时间到了，而还没进入万安寺副本
	if( duration < 5
	 && !me->query_temp("was_job/enter") ){
		 //销毁副本空间 
		if (fbroom) 
		{
			
			team = me->query_team();
           	if (team) {		
			for(index=0;index<sizeof(team);index++){
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[index]);
				team[index]->move("/d/was/was");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);	
			}           
			}
			 else me->move("/d/was/was");
			destruct(fbroom);
		}
		tell_object(me,HIY "你赶到万安寺为时已晚，寺内群雄已经被害，任务失败。\n" NOR);
		log_file( "job/was", sprintf("%8s%-10s勇闯万安寺任务，速度太慢失败，经验：%d。",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("was_job");
		me->apply_condition("was_job",-1);
		me->apply_condition("job_busy",10);
		me->apply_condition("was_busy",70);	
		return 0;
	}		
	
	//&& !me->query_temp("was_job")
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
				team[index]->move("/d/was/was");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);	
			}
			}
            
			 destruct(fbroom);
		}
		else {
			me->apply_condition("job_busy",10);
		    me->apply_condition("was_busy",70);	
			me->move("/d/was/was");
		}
		log_file("job/was", sprintf("%8s%-10s勇闯万安寺任务，时间不够失败，经验：%d。",
			me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		return 0;
	}
	
	
	
	if( me->query_temp("was_job/enter") && environment(me) != fbroom) {
		 
	 	if( !present( "menggu wushi", environment(me)) && me->query_temp("was_job/finish") )
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
				team[index]->move("/d/was/was");
				team[index]->apply_condition("job_busy",10);
		        team[index]->apply_condition("was_busy",70);
			}   
			}
           else me->move("/d/was/was");			

			destruct(fbroom);
		}
		log_file( "job/was", sprintf("%8s%-10s勇闯万安寺任务，离开失败，经验：%d。",
		me->query("name"), "("+me->query("id")+")", me->query("combat_exp")),me);
		me->delete_temp("was_job");
		me->delete_temp("fbroom");
		me->apply_condition("was_job",-1);
		me->apply_condition("job_busy",10);
		me->apply_condition("was_busy",70);	
		return 0;
	}
	
	if(
		me->query_temp("was_job/finish") >= 1000//更新成1000层 by renlai
	 ///无具体实际限制 可以放大到9 .... and more
		&& environment(me) == me->query_temp("fbroom")){
		if( present( "menggu wushi", environment(me) ) )
		return 1;	
	  
	    give_raward(me);
	   
		
		return 0;
	}
	
	
	
	/*
	每间隔1 c 来一批 (恢复到5c)				
	5 c 进入准备状态
	*/
	if(environment(me) == fbroom && me->query_temp("was_job") ){
		object npc;	 
				 
		fbroom=environment(me);		
		switch (duration){	
		    case 10:				
				message_vision(CYN "你借助灌木从林，慢慢靠近高塔，利用灯火闪烁之际一个闪身已飘然入塔。\n" NOR, me);
                 break;		
            case 7:				
				message_vision(CYN "你悄悄一路潜行，尽量避开巡逻武士往塔上走去，进入之后才发现塔内远不止十三层，内里空间似乎大有乾坤。\n" NOR, me);
                 break;				
			case 6:				
				message_vision(CYN "塔上不时飘来兵刃碰撞，拳脚击打之声，似乎有人正在打斗。\n" NOR, me);
                 break;				
			case 5:
				message_vision(BLU "又不时传来惨叫，不知是否为塔内被关押的六派群雄所发出。\n" NOR, me);
				break;
			case 3:	
				message_vision(BLU "你来到高塔内的第"+CHINESE_D->chinese_number(me->query_temp("was_job/finish")+1)+"层,四处打量想要找出群雄所在位置。\n" NOR, me);	
				 if ((random(me->query_temp("was_job/finish"))>12) && !me->query_temp("was_quest/save") && me->query("kar")>20 && !QUEST_D->queryquest(me,"was/save"))
				 {				
                      party= me->query("family/family_name");
					  npcname="六派之人";
					  
					  switch (party)
					  {
						  case "峨嵋派": npcname="周芷若" ; break;
                	      case "少林派": npcname="空闻大师"; break;                	
                	      case "武当派": npcname="宋远桥"; break;
                	      case "华山派": npcname="高老者"; break;
						  case "昆仑派": npcname="何太冲"; break;  
                          case "明教": npcname="宗维侠"; break;						  
					  }
					  me->set_temp("was_quest/save",npcname);//救人标记
					  message_vision(BLU "忽然发现房内竟有一人,仔细一看却正是"+npcname+"，$N急忙悄声道：‘你速速离去，我再去救他人。’\n" NOR, me);	
				 }
					  

					
                 //打扫卫生
				for( i=0; i < sizeof(ob); i++ )
	               {
                       // || 					   
		               if (ob[i]->is_corpse() ||!ob[i]->is_character()) {
					       destruct(ob[i]);					      
				         }
     			   }
                fbroom->set("short", HIM"第"+CHINESE_D->chinese_number(me->query_temp("was_job/finish")+1)+"层塔-副本"NOR);
				break;						
			case 2:					
				message_vision(RED" 突然之间，宝塔上亮起火光，有人手执火把缓缓移动，火把从塔顶亮起，一路下来，到了这层。\n"NOR, me);
				
 				 me->add_temp("was_job/finish",1);				 
		        //guan= me->query_temp("was_job/finish");
				npc = new(JOB_NPC);
                npc->set("targat",me);				
				npc->move(environment(me));
				
				npc = new(JOB_NPC);
				npc->set("targat",me);
				npc->move(environment(me));
				
				
				me->delete_temp("was_up");//允许上楼
				
				if (me->query_temp("was_job/finish")>10)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}
				
				if (me->query_temp("was_job/finish")>40)
				{
					npc = new(JOB_NPC);
				    npc->set("targat",me);
				    npc->move(environment(me));				
				}
				if (me->query_temp("was_job/finish")>60)
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
		
	me->apply_condition("was_job", duration-1);
	
	if(duration==2)
	{
		me->apply_condition("was_job", 900);
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
	int wasscore;
		
	if(!me) return;
			
	
	 team = me->query_temp("was_job/team");//防止作弊
	 //team = me->query_team();
	 fbroom = me->query_temp("fbroom");
		
	j = me->query_temp("was_job/finish");
    finish=me->query_temp("was_job/finish");
	if (me->query("relife/times"))
	{
		x=j+random(1+j);
	}else x=random(j+1);
	
	x=(int)x/4;
	
   //保留最高记录
    if (finish>me->query("was_job/level")) me->set("was_job/level",finish);    

    note=allocate_mapping(4);
    note["player"]=	me->name(1)+"("+capitalize(getuid(me))+")";
	note["playerid"]=capitalize(getuid(me));
	note["waslevel"]=finish;
	note["wasexp"]=me->query("combat_exp");

	if (file_size("/log/wastop") > 0) 
	{	
	   file = read_file("/log/wastop");	
	   notes=restore_variable(file);
	}
 
   if ( !pointerp(notes) || !sizeof(notes))
	{
		 notes = ({ note });
		 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺"+CHINESE_D->chinese_number(finish)+"层成功，成为万安寺闯关记录保持者！\n"NOR);
		 me->set_temp("title", MAG"万安寺"+HIC"头号扛把子"NOR);
	}
    else
	{
		for(k = 0;k<sizeof(notes);k++) {
			if (finish>notes[k]["waslevel"]) {
				
				notes[k]["waslevel"]=finish; 
                notes[k]["wasexp"]=me->query("combat_exp");
               	me->set_temp("title", MAG"万安寺"+HIC"头号扛把子"NOR);		
				
			 if (notes[k]["playerid"]==capitalize(getuid(me)))
				 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺"+CHINESE_D->chinese_number(finish)+"层成功，刷新了自己的记录成为万安寺闯关记录保持者！\n"NOR);
				 else
				 {					 
					 CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺"+CHINESE_D->chinese_number(finish)+"层成功，超过了"+ notes[k]["player"] + "成为万安寺闯关记录保持者！\n"NOR);
					 
					 notes[k]["playerid"]=capitalize(getuid(me));
                     notes[k]["player"]=me->name(1)+"("+capitalize(getuid(me))+")";	
				 }
				 				
                break;				
			}			
		}
	}	
	
	write_file("/log/wastop",save_variable(notes),1);
	
	  if (finish>=1000) {
		  //能上1000层的，有没有九阴也无所谓了。grin
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺"+CHINESE_D->chinese_number(finish)+"层成功，奖励九阴真经上册一部！\n"NOR);
		  me->set("quest/jiuyin1/pass",1);
		  QUEST_D->setmytitle(me,"jiuyintitle",HIR"武林神话"NOR"·"HIC"九阴真经传人"NOR);
	  }
	  
	
	  
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
			tell_object(me,"出得塔来，忽见张无忌迎面走来，偷偷递给你一件事物。\n");
		}		 
	 }
	  
	  
		 
	 me->delete_temp("was_up");//允许上楼
	if( !team ){
       //单人		
		me->apply_condition("job_busy",10);
		me->apply_condition("was_busy",60);
		me->delete_temp("was_job");		
		me->clear_condition("was_job");
		me->set("job_name", "勇闯万安寺");
		//write("现在是单人副本任务奖励，若你是组队模式，请保存完整job日志并联系wiz。\n");
		//x是通宝 目前无效
          if(j > 1 && j <= 10 )
			  TASKREWARD_D->get_reward(me,"勇闯万安寺",2,1,x,0,1,j-1,500);             
          else if(j == 1)
			 TASKREWARD_D->get_reward(me,"勇闯万安寺",2,1,x,0,1,1,160);             
          else if(j>20 && j<=30)
			  TASKREWARD_D->get_reward(me,"勇闯万安寺",2,1,x,0,3,j,4000);
		  else if(j>30 && j<=40) 
			 TASKREWARD_D->get_reward(me,"勇闯万安寺",2,1,x,0,4,j+1,6000);
		  else if(j>40 && j<=50) 
			TASKREWARD_D->get_reward(me,"勇闯万安寺",2,1,x,0,5,j+1,8000);
		  else if(j>50) 
			TASKREWARD_D->get_reward(me,"勇闯万安寺",2,1,x,0,5,j+1,10000);            
		  else TASKREWARD_D->get_reward(me,"勇闯万安寺",2,1,x,0,2,j,800);
		  

		  if( me->query_condition("fx_busy") > 50 )
			me->apply_condition("fx_busy",50);
		 
		 //加入was积分
		 wasscore=0;
            if (finish>10 && finish<=20)
			{
			    wasscore=1;	
			}
			else if (finish>20)
			{
				wasscore=finish;;
			}
			
			
		 if (finish>10) {		   
			me->add("was_job/wasscore",wasscore);
			tell_object(me,HIY "因为闯万安寺成功，你获得了"+CHINESE_D->chinese_number(wasscore)+"点万安寺积分。\n" NOR);
		 }		
	

      if (environment(me) == fbroom) {				
				message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,me);
			    me->move("/d/was/was");
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
				
		   wasscore=0;
            if (finish>10 && finish<=20)
			{
			    wasscore=1;	
			}
			else if (finish>20)
			{
				wasscore=finish;
			}
					 		
		
		for(i = 0;i<sizeof(team);i++){
			if(objectp(team[i]) && userp(team[i])) {
				write("队员信息:"+team[i]->query("name")+"\n");
					team[i]->apply_condition("job_busy", 10);
					team[i]->apply_condition("was_busy",60);
					team[i]->delete_temp("was_job");
					team[i]->clear_condition("was_job");
					team[i]->set("job_name", "勇闯万安寺");
					if (team[i]->query("relife/times"))
					{
						y=j+random(1+j);
					}
					else y=random(j+1);
					
					y=(int)y/4;	

                                  if(j > 1 && j <= 10 )
									  TASKREWARD_D->get_reward(team[i],"勇闯万安寺",2,1,y,0,1,j-1,500);
                                     
                                  else if(j == 1)
									  TASKREWARD_D->get_reward(team[i],"勇闯万安寺",2,1,y,0,1,1,160);
                                   else if(j>20 && j<=30) 
									   TASKREWARD_D->get_reward(team[i],"勇闯万安寺",2,1,y,0,3,j+1,4000);
								   else if(j>30 && j<=40) 
									   TASKREWARD_D->get_reward(team[i],"勇闯万安寺",2,1,y,0,4,j+1,6000);
								   else if(j>40 && j<=50) 
									   TASKREWARD_D->get_reward(team[i],"勇闯万安寺",2,1,y,0,5,j+1,8000);
								   else if(j>50) 
									   TASKREWARD_D->get_reward(team[i],"勇闯万安寺",2,1,y,0,5,j+1,10000);
                                  else
									 TASKREWARD_D->get_reward(team[i],"勇闯万安寺",2,1,y,0,2,j,1000);
                                    

					if( team[i]->query_condition("fx_busy") > 50 )
						team[i]->apply_condition("fx_busy",30+random(20));
					
	
					if (environment(team[i]) == fbroom) {				
				         message_vision(HIY"一阵天旋地转，$N一阵恍惚，才发现自己退出了副本空间。\n"NOR,team[i]);
				         team[i]->move("/d/was/was");
				}					
					
				}
				if (finish>10) {
				team[i]->add("was_job/wasscore",wasscore);
				tell_object(team[i],HIY "因为闯万安寺成功，你获得了"+CHINESE_D->chinese_number(wasscore)+"点万安寺积分。\n" NOR);
			    
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
	
	if (finish>19 && me->query("quest/倚天屠龙记/华山之巅/over") && !me->query("quest/倚天屠龙记/was/pass") && random(finish)>20) 
	{
		CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺成功，并救出六派高手！\n"NOR);
		message_vision(CYN "这时昆仑、崆峒、华山、武当诸派高手早已蜂拥而出。只少林派空闻、空智两位神僧不失前辈风范，过来合十向$N道谢，和宋远桥、俞莲舟等相互谦让一番，始先后出门。\n" NOR, me);
        message_vision(CYN "$N相援六派高手下塔，内力几已耗尽，这时几乎路也走不动了。\n$N默运内功，这才内力渐增。\n" NOR, me);
		me->set("quest/倚天屠龙记/jiuyangzhenjing/combat_exp",me->query("combat_exp"));
	    if(QUEST_D->job_questing(me,4,"倚天屠龙记/was","勇闯万安寺",5000,"不计算",-1,""))
	      {
			  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "因营救六派成功，并得到张无忌的青睐！\n"NOR);
			  message_vision(CYN "忽然从$N耳边传来声音，却是张无忌用传音入秘方式告知$N一个秘密。\n" NOR, me);
              QUEST_D->setmytitle(me,"wastitle",HIY"万安寺有缘人"NOR);					  
	      }  
	}
	
	 else if (me->query_temp("was_quest/save"))
	{
		//CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺成功，有幸救得"+me->query_temp("was_quest/save")+"！\n"NOR);
	    if (QUEST_D->job_questing(me,3,"was/save","勇闯万安寺",1000,"不计算",-1,""))
		{
			QUEST_D->setmytitle(me,"wastitle",HIY"万安寺大英雄"NOR);
			CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "因营救六派成功，并得到"+me->query_temp("was_quest/save")+"青睐！\n"NOR);
			 message_vision(CYN "忽见"+me->query_temp("was_quest/save")+"把$N拉过一旁，在$N耳边说了什么，$N似乎兴奋不已。\n" NOR, me);
		}
		else CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "营救六派成功，可惜机缘未到，未得"+me->query_temp("was_quest/save")+"青睐！\n"NOR);
        me->delete_temp("was_quest/save");		
	}	
	
	else if (finish<15) CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "刺探万安寺获取到了一些情报！\n"NOR);	
    else
        CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")" + "闯万安寺成功，可惜并未救得六派高手，失去了一次机缘！\n"NOR);
		
    me->delete_temp("fbroom");
	me->delete_temp("was_job");
	me->clear_condition("was_job");//防止Bug
}
