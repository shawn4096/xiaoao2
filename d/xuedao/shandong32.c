// nroad6.c
// Modified by Java Apr.27 1998
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short","������");
        set("long",@LONG
����һ��Ѫ���������ң���Ϊ���ء����߼�Ϊ���㣬ǽ�Ƕѷ���
���ٻ����ˣ���Щ�����Ļ����˷���ǽ�ǣ�ǽ������˲��ٲʻ棬��
�д����������ڻ�ϲ����ͼ�Ρ����߿�ǽ�ļ����ϰڷ���һ�Ѷѵ�
ֽ��( paper)������ɢ�伸����ֽ����Ȼ�������ڴ�����ĳ�ֹ�����
�¡�
LONG );
        set("exits",([
                "east"   : __DIR__"shandong3",
                //"southup" : __DIR__"nroad5",
        ]));
        set("objects",([
             /*  "/clone/weapon/miandao" : 1,
				
				"/clone/weapon/xinyuedao" : 1,*/
				"/clone/weapon/blade" : 1,

        ]));
		set("item_desc", ([
			"paper" : CYN"�����ϰڷ���һ�Ѷѵ�ֽ��,��Ѫ���ŵ����Ե�����pi��ֽ�����á�\n"NOR,
			//"shujia" : CYN"����Ϸ���һ�Ѷѵ������ؼ����󲿷�Ϊ�����ɵĵ��׺͹����书��\n"NOR,
		]));

        //	set("no_clean_up", 0);
       // set("outdoors", "xuedao");
        setup();
       //        replace_program(ROOM);
}
void init()
{
	object me=this_player();
	if (me->query("quest/xd/xddf/pizhi/asklaozu"))	add_action("do_pi","pi");
}

int do_pi(string arg)
{
	object me,weapon;
	me=this_player();	
	weapon=me->query_temp("weapon");	
	if (!arg||arg!="ֽ��")
	{
		message_vision(HIW"$N�õ��Կ�������������!\n"NOR,me);
		return 1;
	}
	
	if (weapon&&weapon->query("skill_type")!="blade")
	{
		message_vision(HIW"$N��ϰѪ���������ܵ��ҵ���װ���ɣ�\n"NOR,me);
		return 1;
	}
	if (!me->query("quest/xd/xddf/pizhi/asklaozu"))
	{
		message_vision(HIW"$Nû�еõ������ָ�㣬�����˰��첻��Ҫ�죡\n"NOR,me);
		return 1;
	}
	
	if (me->query_skill("xuedao-daofa",1)<500)
	{
		message_vision(HIW"$N����һ��ֽ��һ��������ȥ��һ���Ӱ�����ֽ����ɢ�ڵأ�\n"NOR,me);
		return 1;
	}
	
	if (me->query("family/family_name")!="Ѫ����")
	{
		message_vision(HIW"$N����Ѫ���ŵ��ӣ�������ǲô��\n"NOR,me);
		return 1;
	}
	
	if (QUEST_D->queryquest(me,"xd/xddf/pizhi"))	
	{
		me->set("title",HBRED"Ѫ����������"NOR);
		me->set("mytitle/quest/xddftitle",HBRED"Ѫ����������"NOR);
		message_vision(HIW"$N�Ѿ��⿪��������⣡\n"NOR,me);
		return 1;
	}
    
	if (QUEST_D->queryquesttime(me,"xd/xddf/pizhi"))	
	{		
		message_vision(HIW"$N����̫Ƶ���ˣ��书��ɻ��������꣡\n"NOR,me);
		return 1;
	}
	if (!me->query("quest/xd/dichuan"))
	{
		//command("say ��");
		message_vision(HIW"$N�ǵմ���Ѫ����Ҫ����ʼ����һ���ҳϵ��ӡ�\n"NOR,me);
		return 1;
	}
	if (me->query("int")<45)
	{
		//command("say ��");
		message_vision(HIW"��ϰѪ��������Ҫ���Ǹ����ԣ�$N���Ǻú�����ȥ�ɣ�\n"NOR,me);
		return 1;
	}
	if (me->query_temp("quest/xd/xddf/liandao"))
	{
		message_vision(HIW"$N������ϰ��ֽ������\n"NOR,me);
		return 1;

	}
	
	message_vision(HIW"$N��ʹ���洫�ڵ��������ţ��ٵ������Ƕ�ֽ�ţ�\n"NOR,me);
	me->set_temp("quest/xd/xddf/liandao",1);
	me->start_busy(2);
	remove_call_out("liandao");
	call_out("liandao",1,me);
	return 1;
	
}

int liandao(object me)
{
  int i,j; 
  if(!me) return 0;	
  
  if(me->query_temp("canwu_liandao")<(10+random(10)))
   {  
	  me->add_temp("canwu_liandao",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n��һ��������һ��С�İ�һ��ֽ��ɢ�ڵ�.\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n����ϸ��ĥ�õ��ļ��ɣ�һ������������ʮ����ֽ��\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n����������������ÿһ����û���ƺã����в��ɴ󼱣�..\n"NOR);
			 me->add_temp("canwu_liandao",-1);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ��������룬Ȼ����һ�����������յ����������ɣ��ƺ������ĵ�.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ���������.\n"NOR);
			me->add_temp("canwu_liandao",-1);

			break;
		case 5:
			tell_object(me,MAG"\n�����з��겻����һ��������ȥ��������ŭ.\n"NOR);
			me->add_temp("canwu_liandao",-1);

			break;
		default:tell_object(me,YEL"\n���Ȼ�ƺ������ã�һ����������Ȼ����������ֽ��.\n"NOR);
			break;

	  }      

	  tell_room(environment(me),HIC""+me->query("name")+"���ó�����һ��һ�������Ƕ�ֽ�ѣ����鼫Ϊרע...\n"NOR, ({}));

	  //remove_call_out("liandao");
	  call_out("liandao",3+random(3), me);

   } 
  else	
 	{ 
          if (QUEST_D->questing(me,2,150,0,"xd/xddf/pizhi"))
		  {        
         me->start_busy(3);
		 message_vision(HIY"\n$Nһ���������ں���ֽ����ֻ����һ��ֽ������ֽ�ڵ��������£���ƮƮ����ء���\n"NOR,me); 
         message_vision(HIY"\n$N���������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HBYEL+HIW"\n$N�������ϵ�����ϰ��������������Ѫ�����������ڵ���ֽ�������İ��أ���\n"NOR,me); 
        
		 me->delete_temp("canwu_liandao");
		 me->delete_temp("quest/xd/xddf/liandao");
		 QUEST_D->setmytitle(me,"cxztitle",HBRED"Ѫ�������洫"NOR);		 
		 return 1;
        }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������ֽ���������ǲ��ýⰡ������Ŭ���ɡ���\n"NOR,me); 
		 message_vision(HIY"\n������ֽ��������������ʧ�ܣ�\n"NOR,me);          
		 me->start_busy(2);
		 me->delete_temp("canwu_liandao");
		 me->delete_temp("quest/xd/xddf/liandao");
		 me->delete_temp("quest/xd/xddf");
		 return 1;
       }
	}	
}