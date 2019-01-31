// gmd.c  光明顶
// Modify By River@SJ 99.06
// 添加围攻光明顶副本 by renlai
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{ 
       set("short",HIR"光明顶"NOR);
       set("long", "
    这里就是明教光明顶。你走到这里就可看见三个鲜红色大字。明教，少林，\n"+
"丐帮中明教是最大的教，少林是最大的门派，而丐帮则是最大帮派。明教自由\n"+
"波斯总教传至中原已有百多年的历史了。明教始终都以反元抗胡，行善去恶及\n"+
"除暴安良为自已的宗旨。但由于明教太大，门下教众难免莨莠不齐，至使被名\n"+
"门正派称为魔教。正中央一面红色火焰的大旗。北边是练武场，南边是巨木旗\n"+
"的所在地。\n\n"HIR"\t\t\t光    明    顶\n\n"NOR);
	set("exits", ([
		"northup" : __DIR__"wu3",
		"southdown" : __DIR__"muqi",			
	]));
	set("objects",([
                "kungfu/class/mingjiao/yin" : 1,
                CLASS_D("mingjiao") + "/wulu" : 1,
                __DIR__"npc/m-dizi" : 2,
	]));
        set("outdoors", "明教光明顶");
        set("valid_startroom", 1);
        set("coor/x",-290);
	set("coor/y",170);
	set("coor/z",110);
	set("coor/x",-290);
	set("coor/y",170);
	set("coor/z",110);
	setup();        
        call_other("/clone/board/mingjiao_b","???");
}

int init()
{
	object me=this_player();	
	if (me->query_temp("gmd_job/asked")) 
	{
        set("long", "
    这里就是明教光明顶。你走到这里就可看见三个鲜红色大字。明教，少林，\n"+
"丐帮中明教是最大的教，少林是最大的门派，而丐帮则是最大帮派。明教自由\n"+
"波斯总教传至中原已有百多年的历史了。明教始终都以反元抗胡，行善去恶及\n"+
"除暴安良为自已的宗旨。但由于明教太大，门下教众难免莨莠不齐，至使被名\n"+
"门正派称为魔教。正中央一面红色火焰的大旗。北边是练武场，南边是巨木旗\n"+
"的所在地。此时光明顶上已经聚集了六派群雄，随时准备围攻(weigong)光明顶。\n\n"HIR"\t\t\t光    明    顶\n\n"NOR);		
		add_action("do_weigong","weigong");			
	}	
}

int do_weigong()
{
	object me=this_player();
	object fbroom;
	object *team,*ob;
	int max,i,j;	
	   
	   team = me->query_team();	
	   
	   if (me->query_condition("gmd_job")<5) 
	   {
		   write("你来晚了,已经错过了进攻光明顶的最佳时机。\n");			  
			  return 1;
	   }
		
		if (team)
		{
			if (me->query_temp("gmd_job/team")!=team) {
			  write("组队改变了,无法进入光明顶。\n");
			  
			  return 1;
		  }

          fbroom= new("/u/anger/gmdfb");//进入fb
          fbroom->set("backroom","/d/mingjiao/gmd");//返回路径
		  fbroom->set("short", HIM"光明顶-副本"NOR);
		  fbroom->set("leader",me);//保存队长
		  
          me->set_temp("fbroom",fbroom);//记录副本
          me->set_temp("gmd_up", 1);		  
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")一行数人预备围攻光明顶扑灭圣火！\n"NOR);
		for (i=0;i<sizeof(team);i++){			
		
		if (team[i]->query_condition("killer")) 
		{ 
	        write("队中有人在被通缉,无法进入光明顶。\n");
			break;
			//return 0;
		}		
		if (!present(team[i])){			
			write("好象人不全啊？"+team[i]->query("name")+"怎么没来,无法进入光明顶。\n");
			break;
			//return 0;
		}
		
		ob = deep_inventory(team[i]);
	         j = sizeof(ob);
	            while (j--)
	               if (ob[j]->is_character()){
					   ob[j]->move("/d/mingjiao/gmd");
		               write("你身上背负一个人，无法进入副本。\n");
		                      return 1;
	                       }	
		
		    team[i]->set("job_name", "围攻光明顶");
			message_vision(HIC"$N等人肆无忌惮，一窝蜂的往光明顶上冲入。\n"NOR,team[i]);
			team[i]->move(fbroom);
		
		}	  
		
		return 1;
		}
		
		else 
		{		
		
		if (me->query_condition("killer")) 
		{
             write("你在被通缉,无法进入光明顶。\n");			
		      return 1;//防止通缉犯躲进副本		
		}
		
		ob = deep_inventory(me);
	       j = sizeof(ob);
	       while (j--)
	      if (ob[j]->is_character()){
			  ob[j]->move("/d/mingjiao/gmd");
		      write("你身上背负一个人，无法进入副本。\n");
		      return 1;
	         }
		  
		 	
          fbroom= new("/u/anger/gmdfb");//进入fb
          fbroom->set("backroom","/d/mingjiao/gmd");//返回路径
          fbroom->set("short", HIM"光明顶-副本"NOR);		  
		  me->set_temp("fbroom",fbroom);//记录副本
		  me->set_temp("gmd_up", 1);
		  fbroom->set("leader",me);//保存队长
		  CHANNEL_D->do_channel(this_object(), "rumor", HIC"听说" + me->name(1)+"("+me->query("id")+")孤身一人独闯光明顶！\n"NOR);
		  message_vision(HIC"$N仗着艺高人胆大竟然一人直闯光明顶。\n"NOR,me);		  
          me->move(fbroom);	
		  return 1;
		}	
	
}
