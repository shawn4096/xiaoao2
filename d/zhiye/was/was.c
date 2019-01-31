//万安寺副本 by renlai

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", HIM"万安寺外"NOR);
        set("long", @LONG
万安寺房舍众多，规模之大，几和少林寺相仿佛，内有好大一座丛林，寺内
有三尊大铜佛，寺楼高数层，寺后的一座十三级宝塔更老远便可见，塔上人
影绰绰，每一层中都有人来回巡查，塔下更有二三十人守着。
LONG);
        set("outdoors", "万安寺");		
        set("quest",1);
		set("no_sleep_room",1);
		set("no_quit", 1);
		set("exits", ([
		"south" : "/d/cangzhou/nroad2",		
	]));
        
		
   setup();
}
int init()
{
	object me=this_player();	
	if (me->query_temp("was_job/asked")) 
	{		
		add_action("do_yingjiu","yingjiu");			
	}	
}

int do_yingjiu()
{
	object me=this_player();
	object fbroom;
	object *team,*ob;
	int max,i,j;	
	   
	   team = me->query_team();	
	   
	   if (me->query_condition("was_job")<5) 
	   {
		   write("你来晚了,已经错过了进入万安寺的最佳时机。\n");			  
			  return 1;
	   }
		
		if (team)
		{
			if (me->query_temp("was_job/team")!=team) {
			  write("组队改变了,无法进入万安寺。\n");
			  
			  return 1;
		  }

          fbroom= new("/u/anger/wasfb");//进入fb
          fbroom->set("backroom","/d/was/was");//返回路径
		  fbroom->set("short", HIM"万安寺塔底层-副本"NOR);
		  fbroom->set("leader",me);//保存队长
		  
          me->set_temp("fbroom",fbroom);//记录副本
          me->set_temp("was_up", 1);		  
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行数人预备潜入万安寺救人！\n"NOR);
		for (i=0;i<sizeof(team);i++){			
		
		if (team[i]->query_condition("killer")) 
		{ 
	        write("队中有人在被通缉,无法进入万安寺。\n");
			break;
			//return 0;
		}		
		if (!present(team[i])){			
			write("好象人不全啊？"+team[i]->query("name")+"怎么没来,无法进入万安寺。\n");
			break;
			//return 0;
		}
		
		ob = deep_inventory(team[i]);
	         j = sizeof(ob);
	            while (j--)
	               if (ob[j]->is_character()){
					   ob[j]->move("/d/was/was");
		               write("你身上背负一个人，无法进入副本。\n");
		                      return 1;
	                       }	
		
		    team[i]->set("job_name", "勇闯万安寺");
			message_vision(HIC"$N等了一会，见四下确实无人，这才从后门中闪身鱼贯而入。\n"NOR,team[i]);
			team[i]->move(fbroom);
		
		}	  
		
		return 1;
		}
		
		else 
		{		
		
		if (me->query_condition("killer")) 
		{
             write("你在被通缉,无法进入万安寺。\n");			
		      return 1;//防止通缉犯躲进副本		
		}
		
		ob = deep_inventory(me);
	       j = sizeof(ob);
	       while (j--)
	      if (ob[j]->is_character()){
			  ob[j]->move("/d/was/was");
		      write("你身上背负一个人，无法进入副本。\n");
		      return 1;
	         }
		  
		 	
          fbroom= new("/u/anger/wasfb");//进入fb
          fbroom->set("backroom","/d/was/was");//返回路径
          fbroom->set("short", HIM"万安寺塔底层-副本"NOR);		  
		  me->set_temp("fbroom",fbroom);//记录副本
		  me->set_temp("was_up", 1);
		  fbroom->set("leader",me);//保存队长
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")孤身一人独闯万安寺！\n"NOR);
		  message_vision(HIC"$N等了一会，见四下确实无人，仗着艺高人胆大竟然一人从后门中闪身而入。\n"NOR,me);		  
          me->move(fbroom);	
		  return 1;
		}		  
	
	
}

