// qqchi.c ��ǧ��
// By River 99.5.25
#include <ansi.h>
inherit NPC;
string ask_dan();
string ask_quest();
string ask_tuzaohe();
string ask_pojie();

void create()
{
	set_name("��ǧ��", ({ "qiu qianchi", "qiu", "qianchi"}));
	set("nickname", HIY"��������"NOR);
	set("title",HIW"�����Ů����"NOR);
	set("long","һ����������ͺͷ������ϥ���ڵ��£�����ŭ�ݣ���Ȼ������\n"); 
	set("gender", "Ů��");
	set("age", 55);
	set("attitude", "friendly");

	set("unique", 1);
	set("shen_type", -20);

	set("str", 35);
	set("int", 30);
	set("con", 28);
	set("dex", 5);
	set("per", 8);

	set("max_qi", 20000);
	set("max_jing", 20000);
	set("neili", 25000);
	set("max_neili", 25000);
	set("eff_jingli",20000);
	set("jiali", 200);
	set("combat_exp", 9500000);
	set("score", 20000);

	set_skill("force", 460);
	set_skill("guiyuan-tunafa", 460);
	set_skill("dodge", 460);
	set_skill("shuishangpiao", 460);
	set_skill("strike", 460);
	set_skill("tiezhang-zhangfa", 460);
	set_skill("parry", 450);
	set_skill("literate", 100);

	map_skill("force", "guiyuan-tunafa");
	map_skill("dodge", "shuishangpiao");
	map_skill("strike", "tiezhang-zhangfa");
	map_skill("parry", "tiezhang-zhangfa");
	prepare_skill("strike", "tiezhang-zhangfa");

	set("inquiry", ([ 
		"���鵤" : (: ask_dan :),
		"����ֹ" : (: ask_quest :),
		"�ƽ�𵶺ڽ�" : (: ask_pojie :),
		"����˾���" : (: ask_tuzaohe :)
	]));
	setup();
}

void kill_ob(object who)
{
	object me;
	object weapon;
	object ob;
	me=this_player();
	weapon = me->query_temp("weapon");
	ob=this_object();
	if (living(ob)) {
		command("sneer " + me->query("id"));
		if( weapon ){
			message_vision(HIW"$NͻȻ����һ�������зɳ�һ�� ���һ�죬����$n�������յ���"+weapon->query("unit")+weapon->name()+HIW"�ϡ�\n"NOR,ob,me);
			weapon->move(environment(ob));
			me->add_busy(2);
			message_vision(HIR"\n$Nֻ���ֱ۾�����ָ��Ȼ����ס������һ����"+weapon->name()+HIR"���ڵ��¡�\n"NOR,me);
		}
		else {
			message_vision(HIW"$N������˶��Ѽ���������ƿ�֮�������Х��ֱָ$nС����ȥ�Ƶ����Ǻ������ס�\n"NOR,ob,me);
			me->add_busy(2);
			message_vision(HIR"\n$N��������һ���߽У�����������������ȥ��\n"NOR,me);
			me->receive_damage("qi", me->query("eff_qi")/2);
			me->receive_wound("qi",  me->query("eff_qi") /2);
		}
	}
	::kill_ob(me);
}

string ask_dan()
{
	if(this_player()->query_temp("jqg/chi"))
		return "��λ"+RANK_D->query_respect(this_player())+"���Ҳ����Ѿ������㣬���鵤����֮����ô��";
	this_player()->set_temp("jqd/chi", 1);
		return "�����ڴ�����������Ե�������Ψһһ�ž��鵤�Ҳ��ڴ����������ש�¡�";
}

string ask_quest()
{
	object me = this_player();

	if(me->query_temp("quest/jindao"))
		return "��λ"+RANK_D->query_respect(this_player())+"���㻹��ȥ����ֹ���ұ������ǲ��ǲ����ַ����ˣ�";
		
  if( me->query("combat_exp") < 2000000 )
        	return "���㵱ǰ�ľ�����»��������ұ��𣬻���ץ��ȥ����ȥ�ɡ�\n";
 
	me->set_temp("quest/jindaoheijian/jueqingdan", 1);
		return "�ߣ���������ҵ���˵ز�����ɱ��������ǧ���Ĳ�Ϊ�ˣ�������ܽ����鵤�������Ҿͽ�������һ�����ܡ�";
}

int accept_object(object me, object ob)
{
	if( ob->query("id") == "jueqing dan" ) {
			command("sneer");
			tell_object(me,"20��ǰ�Ҵ����ǧ�ɱ����غ����ˣ�\n");
			tell_object(me,"������ܰ���ȥɱ�˻��صĻ���hehe��\n");
			call_out("destructing", 1, ob); 
			me->set_temp("quest/jindaoheijian/jueqingdan",0);
			me->set_temp("quest/jindaoheijian/huangrong",1);
			return 1;
		  }
		else {
			command("say ��Ȼ�üپ��鵤��ƭ��,������");
			me->fight_ob(this_object());
			this_object()->kill_ob(me);
			me->set_temp("quest/jindaoheijian/jueqingdan",0);
			call_out("destructing", 1, ob); 
			return 1;
		     }
	return 1;
}
void destructing(object ob)
{
	if (ob) destruct(ob);
}


string ask_tuzaohe()
{
	object me=this_player();
	me->start_busy(10);
	
	if (me->query("quest/tiezhang/gytnf/pass"))
		return "���Ѿ�ȫ������������˾�����\n";
	if (time()-me->query("quest/tiezhang/gytnf/time")<86400)
		return "������̫�ڿ��ˣ�\n";
	if (me->query("family/family_name")!="���ư�")
		return "�㲻�����ư���ӣ�����������\n";
	if (me->query_temp("quest/jindaoheijian/huangrong")) 
	{
		   message_vision(HIC"��������ҳ����������ҵ����鵤�ķ��ϣ��Ҿ͸��������ž����İ��أ��㸽����������˵��������\n"NOR,me);
		   command("say ���ɰٴ����ƺ�����������֮��\n");
		   command("say ����һ�ߣ���Ȼ������\n");
           me->start_busy(999);
		   remove_call_out("thinking");
		   call_out("thinking",1,me);
		   me->delete_temp("quest/jindaoheijian/huangrong");
		   
	}else {
		message_vision(CYN"��ǧ�ߺٺ���Ц������˵�����������һؾ��鵤��˵��\n"NOR,me);
	}
	return "��ǧ������ؿ�����һ�ۣ�Ŀ������˸������\n";
}

int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(10);

  me->set("quest/tiezhang/gytnf/time",time());

  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ������������˾���ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_tuzaohe")<(15+random(10)))
   {  
	  me->add_temp("canwu_tuzaohe",1);

	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n�㽫ʦ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
			break;
		case 1:
			tell_object(me,HIY"\n��Ȼ�����ƺ�ץס��һЩ����\n"NOR);
			break;
		case 2:
			 tell_object(me,HIR"\n���������״̬������һƬ�������ƺ�Ҫץס�Ǹ������ˣ�..\n"NOR);
			break;
		case 3:
			tell_object(me,HIW"\n������Ķ����������ģ������������ƺ���Щ����.\n"NOR);
			break;
		case 4:
			tell_object(me,CYN"\n�������������ƣ��֮�ʣ��ƺ�����ƿ����..\n"NOR);
			break;
		case 5:
			tell_object(me,MAG"\n��˼άƯ���ڿ��У�����Ӥ����ԡ.������ˬ.\n"NOR);
			break;
		default:tell_object(me,YEL"\n��̾��һ�������������ǲ�����Ч����.\n"NOR);
			break;

	  }
      

	  tell_room(environment(me),HIC""+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));
	
	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);
	  return 1;

   } 
   else if (i>=25
			&& j<3
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n\n$N�������������������������ھ�����˵İ��أ���Ԫ���ɷ���Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/tuzaohe", sprintf("%s(%s) �ɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ������Թ�Ԫ������˵İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tiezhang/gytnf/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/tiezhang/gytnf/time",time());
		 me->set("quest/tiezhang/gytnf/pass",1);
		 me->delete_temp("canwu_tuzaohe");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n����������������˵Ľ���ʧ�ܣ�\n"NOR,me); 
         log_file("quest/tuzaohe", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܹ�Ԫ��������˾�������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tiezhang/gytnf/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/tiezhang/gytnf/fail",1);
		 me->set("quest/tiezhang/gytnf/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_tuzaohe");
		 return 1;
   }

}

string ask_pojie()
{
	int i,j; 
	object me;
	me=this_player();
	  if(!me) return "";
	  i = 20;
    if(me->query("m-card-vip")) i =  18;
    if(me->query("y-card-vip")) i =  15;
    if(me->query("buyvip"))     i =  10;
    i=random(i);
	j=random(me->query("kar"));

    
	if (me->query("quest/tz/jdhj/pass"))
		return "���Ѿ�ȫ���������ƽ�𵶺ڽ����أ�\n";
	if (time()-me->query("quest/tz/jdhj/time")<86400)
		return "������̫�ڿ��ˣ�\n";
	if (me->query("family/family_name")!="���ư�")
		return "�㲻�����ư���ӣ�����������\n";
	if (me->query("quest/jindaoheijian/pass")) 
	{
		   message_vision(HIC"��������ҳ����������ҵ����鵤�ķ��ϣ��Ҿ͸��������ž����İ��أ��㸽����������˵��������\n"NOR,me);
		   command("say ���ǵ������ǽ��������ǽ��������ǵ���\n");
		   command("say �𵶺ڽ������书ֻҪմȾ�Ⱥ�֮��ϱ��ƽ�\n");
		   		   command("say ���书�������ƣ��ҵ����ͷ�Ȱ�Ǹ��Ϲ�Ҫȥ�����������ǲ���\n");
		   		   command("say ��Ȼ������������壬���Ҿͽ������˵��������\n");

		   me->delete_temp("quest/jindaoheijian/huangrong");
		   
	}else {
		message_vision(CYN"��ǧ�ߺٺ���Ц������˵�����������һؾ��鵤��˵��\n"NOR,me);
		return "��ǧ������ؿ�����һ�ۣ�Ŀ������˸������\n";

	 }

	  if (me->query("kar")>30) 
	  {
		  log_file("quest/bug", sprintf("%s(%s) ������������˾���ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
			 me->name(1),
			 me->query("id"),
			 me->query("combat_exp")),
			 me->query("age"),
			 me->query("kar"));
		  return 0;
	  }
 
	  if ( i<3
	  && j>25
	  && random(me->query_int())>30
	  && me->query("kar")<31)
 	  { 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N������������Ц������˵������ԭ����ˣ�ԭ����ˡ���\n"NOR,me); 
         message_vision(HIY"\n\n$N�����������������������ƽ�𵶺ڽ��İ��غ��Ȼ��ͨ����\n"NOR,me); 
         log_file("quest/pojiejdhj", sprintf("%s(%s) �ɹ���ʧ��%d�β���󣬻�Ե�ɺ��£��ɹ������ƽ�𵶺ڽ��İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tz/jdhj/fail"),
		 j,
		 i,
         me->query("combat_exp")));

		 me->set("quest/tz/jdhj/time",time());
		 me->set("quest/tz/jdhj/pass",1);
		 return "��������������������������������������������һ�����֣�\n";
     }
 	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵��������������һ�����񰡡���\n"NOR,me); 
		 message_vision(HIY"\n�����ƽ�𵶺ڽ��Ľ���ʧ�ܣ�\n"NOR,me); 
         log_file("quest/pojiejdhj", sprintf("%s(%s) ʧ�ܣ���%d��ʧ���ƽ�𵶺ڽ���������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/tz/jdhj/fail",1),
		 j,
		 i,
         me->query("combat_exp")));

		 me->add("quest/tz/jdhj/fail",1);
		 me->set("quest/tz/jdhj/time",time());
		 me->start_busy(2);
		 return "���ǻ�����\n";
   }

}

