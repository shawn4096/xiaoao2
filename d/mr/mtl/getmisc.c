// mr up_misc_skills.c
// be jpei 2010

#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
	set("short",HIW"������-���"NOR);
	set ("long",@long
������٢��ɽׯ����书�ؼ��ĵط���һ�������������İڷ��Ÿ�����
�����ƺ�����������޸������������ѧ�йء�
long);
	set("exits",([
		"out" : __DIR__"huandong",
	]));


	set("no_fight", 1);
	setup();
}

void init()
 {
         add_action("do_canwu", "canwu"); 
         add_action("do_canwu", "yandu");
 }

/*

int do_canwu(string arg)
 {
     object me = this_player();

     if(arg != "misc" )
           return notify_fail("����ֻ�ܲ�����ѧ(misc)����!\n");

     if (me->is_busy() || me->is_fighting()|| me->query_temp("con_gift") )
                  return notify_fail("����æ���ء�\n");

if (me->query_temp("canwu_now") )
       return notify_fail("����æ���ء�\n");

if (me->query("relife/gifts/now") )
       return notify_fail("�㻹���Ȱ��Լ����츳��������Ժ������ɡ�\n");
        
        if (query_temp("canwu") )
        return notify_fail("�������ڲ����أ����һ��ѡ�\n");


     if( me->query("combat_exp",1)<25000000)
                 return notify_fail("����ҵķ��˷�����ϵĲ��飬������������ݸ���Ī�⣬�޷���⣬���ɵ�ҡ��ҡͷ��\n");
       
     
       message_vision( HIW"$N��ϸ�ķ���������ϵĲ��飬����������̺�����ѧ���ݺܸ���Ȥ��\n"NOR,me);
        message_vision( HIW"$Nһͷ���������.��ͣ�ķ����š��� \n"NOR, me);
       me->start_busy(100);               
       me->set_temp("canwu_now",1); 
       set_temp("canwu",1);            
     call_out("thinking",5, me );
         return 1;

 }


int thinking(object me)
{
  int i,j,p,exp;
  p = me->query("str",1)+ me->query("dex",1)+ me->query("con",1)+ me->query("int",1);
 if(!me) return 0;
	
 if(me->query_temp("con_gift")<(3+random(3)))
       {  me->add_temp("con_gift",1);
          if(random(2)) tell_object(me,HIG"\n����ϸ���ж�������������ݣ�ֻ���ö�Ŀһ��...\n"NOR);
                   else tell_object(me,HIY"\n���ж�������ǧ��ٹֵ���ѧ���ݣ�������������...\n"NOR);  

	  tell_room(environment(me),HIC""+me->query("name")+"üͷ���壬�ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

	}

 else { 
         me->delete_temp("con_gift");
         me->start_busy(1);     
  message_vision(HIC"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
  tell_object(me,HIR"\n��ͨ�������ж����Դ��������ļ�ʶ��������һ����\n"NOR);
  tell_object(me,HIR"\n�������Լ���ǰ�߹��Ĳ�����·��������к�ڣ����������ʦ�ţ����뽭����\n"NOR);
  tell_object(me,HIW"������һ�����°�ʦ�Ļ��ᣡ\n"NOR);
  tell_object(me,HIR"\n����츳���Ա������ˣ�������������·����Լ����츳����\n"NOR); 
  tell_object(me,HIR"\n�������������Լ�����ʱ��Ц�����������룡\n"NOR);    
  tell_object(me,HIW"������˿��ٳɳ��Ļƽ�ʱ����\n"NOR);    

        me->set("str",10);
        me->set("dex",10);
        me->set("con",10);
        me->set("int",10);
        //me->delete("gf_gives");

		me->delete("class");
		me->set("relife/gifts/total", p-40 );
        me->set("relife/gifts/now",   p-40 );
        me->delete("relife/gifts/used");
        
        
        
        
        
        
        
               exp = 5000000;
       if(me->query("registered") == 3) exp=4500000;
       if(me->query("y-card-vip"))         exp=4250000;
       if(me->query("buyvip") )             exp=4000000; 
       me->add("combat_exp",-exp);
        me->delete("family",1);                  
        me->add_condition("db_exp",6666);
        me->set("age",18);
        me->set("shen",1);
        me->set("title",HIC"������"NOR);
       i = me->query("relife/gifts/now",1); 
       j = me->query("relife/gifts/total",1);
   
    tell_object(me,HBBLU"\n�㱾�β��򹲺ķ���" + HIW + chinese_number( exp ) + HIR + "ʵս���飬�������ܹ���" + HIW + chinese_number( i ) + HIR + "�Ķ�����츳��\n"NOR);
    tell_object(me,HBRED"\n������ʹ��(addgift)���з��䣡\n"NOR);

      log_file("canwu/getmisc", sprintf("%s(%s) �ķ�500���飬�����츳����Ϊ%d����ǰ���飺%d��\n", 
       me->name(1),
       me->query("id"),
       me->query("relife/gifts/total",1),
       me->query("combat_exp")) );
  me->delete_temp("canwu_now");   
 delete_temp("canwu");   
   }

}

*/