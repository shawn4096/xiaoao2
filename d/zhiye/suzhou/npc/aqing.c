// aqing.c ԽŮ����

#include <ansi.h>
inherit NPC;
inherit F_MASTER;

int ask_ynj();
//int thinking();
void create()
{

        set_name("����", ({ "a qing", "aqing", "qing" }) );
	    set("gender", "Ů��" );
        set("age", 14);
		set("per", 40);
        set("long", "һ��ʮ�������С���Ƥ����������ò��������������������������ˡ�\n");
        set("attitude", "peaceful");
        set("beauty", "30");
        set("title", "��Ů");
        set("attitude", "friendly");
        set("combat_exp", 18000000);
        set("str", 30);
        set("dex", 30);
        set("int", 30);
        set("con", 30);
        set("max_neili", 25000);
        set("neili", 25000);
        set("eff_jingli", 8000);
        set("jingli", 8000);
        set("max_jing", 6000);
        set("jing", 6000);
        set("jiali", 200);
        set("max_qi", 30000);
        set("qi", 30000);
        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "sword.liujian" :)
        }));

        set_skill("sword", 600);
        set_skill("dodge",400);
        set_skill("force",  400);
        set_skill("parry",  400);
        set_skill("literate",200);
        set_skill("yunu-xinjing", 400);
        set_skill("yuenu-jian", 600);
        set_skill("yunu-shenfa",500);

        map_skill("force", "yunu-xinjing");
        map_skill("dodge", "yunu-shenfa");
        map_skill("sword","yuenu-jian");
        map_skill("parry","yuenu-jian");
        set_temp("apply/attack", 150); 
        set_temp("apply/defense", 150); 
        set_temp("apply/armor", 150); 
        set_temp("apply/damage", 150); 
        set("inquiry", ([
		   "ԽŮ��" : (: ask_ynj :),
		   	//"����" : (: ask_jueji :),
		  //  "ԽŮ��" : random(2)?"������������һλ��Գ�������ҵ�һ�׽������ؾ���":"��������ģ����������֮�ھͿ������վ��ڹ��ķ����ٺ١�",
		   "���" : "�����ҵĴ�磬���������ʲô��",
		   //"�����似" : "���������ʲô����..�д����������Ű���....",
		
	])); 
        setup();

        carry_object("/d/suzhou/npc/obj/shoe")->wear();
        carry_object("/d/suzhou/npc/obj/skirt")->wear();
        carry_object("/d/suzhou/npc/obj/greensilk")->wear();
        carry_object("/d/suzhou/npc/obj/zhujian")->wield();
}
int ask_ynj()
{
    int total,i,j,t,s;
	object me = this_player();
	
	total=me->query("str")+me->query("con")+me->query("dex")+me->query("int")+me->query("per")+me->query("pur");
	i=random(me->query("kar"));
	j=random(me->query("int"));
	t=random(total);
	//�����
	
	 s = 20;
      if(me->query("m-card-vip")) s =  18;
      if(me->query("y-card-vip")) s =  15;
      if(me->query("buyvip"))     s =  10;
      s=random(s);
	if (me->query("gender")!="Ů��" )
	{
     command("say �����￴�����������˵���ô��");
	 return 1;
	}
	if (me->query("per") < 29)
	{
     command("say ��������ò̫�ѿ�����ô����ϰ��ԽŮ����");
	 return 1;
	}
	if (me->query("quest/ynj/pass") == "ok")
     {
     	 if(me->query("potential")<= 5){
	       command("kick "+me->query("id"));	     
	       command("say Ǳ�ܲ���ѧʲô������");
           return 1;
          }
		 else{
			 message_vision("$N��$n����й�ԽŮ�����İ��\n", me, this_object());
             me->receive_damage("jing", random(30));
             tell_object(me,"�����˰����ָ�㣬��ԽŮ���İ����ƺ���Щ�ĵá�\n");
             me->add("potential",-(random(3)+2));
             if( me->query("potential")<0)
                me->set("potential",0);
             me->improve_skill("yuenu-jian", 150+random(me->query_int()*2));
             me->improve_skill("sword", random(me->query_int())/2);
			 return 1; 
			 }        
	  }
    //else{
   	  //command("say ��Ҫ��Ϸ����������أ����ٿ���ЦС����ɱ���㣡\n");
	  //return 1;
      //}
    if( me->query("combat_exp")<10000000)
	 {
	  command("say ����10m����ѧԽŮ�����㹦��̫ǳ�ˣ�������ȥ�ɡ�");
	  return 1;
	 }

    if( (time()-me->query("quest/ynj/time"))<86400)		
   	{
	  command("say �㻹��ȥ��Ϣһ�°ɣ�û�±������ң�");
	  return 1;
	}
	//me->start_busy(10);
      command("sigh");
	  command("say ԽŮ���������ǿ������ԽŮ���������ǵ�����������ɽ��ʱż����һλ�ϰ�ԳϷˣ���������ѧ���ġ�");
      command("say ��������ʶ��һ�����������������������뷽���˽���������ʱ�����ʿ��");
      command("say �Ȿ�������˼�Ľ�����û�뵽��Ȼ�����˼ǵ�����ɽҰŮ�ӡ�");
	  command("say ���������ѧ�Ϳ���Ļ�Ե�ˣ�");
	  command("say ����ϸ�ˡ���������������");
	  message_vision(HIG"���ཫԽŮ������ʽʩչ��������ʱ������������Ű���ԽŮ���ľ���ʩչ������������˸�������������������һ���������ֵĽ�â��\n"NOR,me);
      message_vision(HIY"������ӣ��������������羪�裬������������ʽ������������Ů��\n"NOR,me);
	  message_vision(HIW"����ͦ��ֱ�̣�ٿ��ٿ������������һ�����磬���в������ǰ�أ�������ɣ�������磡\n"NOR+
                     HIC"����һ�����򣬳���ƽƽ���棬ȥ��ȴ�Ǿ��죬ֱ�������ƿգ�������Ծ��\n"NOR+
                     HIM"Ծ���գ��ؽ��»���$w�ó�������������������˸��������ӷ�к���չ�ɽ����\n"NOR+
                     HIB"���������̳����������縡����Ӱ,��������,����������Ծ,���ݼ��ţ�\n"NOR+
                     HIY"���󽣾���������Ծ�裬�Ȼ����,һ��ƥ����Ľ�âѸ�����䣬���̶�����\n"NOR+
                     HIG"������㣬����������ó���ǧ����Ӱ����Ȧ�����У�������磬����������\n"NOR+
                     HIR"���������˽���һ����â���ǣ��ݺ���裬��ը���꣡ \n"NOR+
                     HIB"����һ������âһ�����գ�ֻ���ǽ���Ѹ����磬����ü�ޣ�Ψ�м��ٷ��ˣ�\n"NOR,me);

     if (i>=28 
		  && s==3
		  && t>200 //����20��⿪
		  && j>40 )
		 {
	      command("smile");
	      command("say �����Ǵ�����������Ȼһ���Ӿ��������ˣ����Ǹ���ľ���ǿ���ˡ�");
	      command("sigh");
	      command("say ������������������ã�");
    	  message_vision(HIC"���Ű����һ����̾����������������ת����ȥ��\nһ���������޵�����������[�������ǵ����⣿���Ǻú���ϧ���°ɡ�]\n"NOR,me);
           
          message_vision(HIR"\n\n��ϲ�㣬���������ָ����������ʹ��ԽŮ���Ѿ������˽��ˣ�ʣ�µľ����ڼ���ϰ�ˣ�\n"NOR,me);
          me->set("quest/ynj/pass","ok");
          me->set("title",HIC"ԽŮ��"NOR);
		  me->set("mytitle/quest/yuenvtitle",HIC"ԽŮ��"NOR);
		  me->set_skill("yuenu-jian",1);
          log_file("quest/yuenujian", sprintf("%s(%s) ��ϲ��ʧ��%d�γɹ��⿪ԽŮ������ǰ����ֵkar(KAR)��%d(%d),��ǰ���ֵ��%d,��ǰ������ԣ�%d(%d),��ǰ���total��%d(%d),��ǰ���飺%d��\n", 
	      me->name(1),
          me->query("id"),
          me->query("quest/ynj/fail"),
		  i,
		  me->query("kar"),
		  s,
		  j,
		  me->query("int"),
		  t,
		  total,
          me->query("combat_exp")));
          me->start_busy(1);
		  return 1; 
	    }
     else
       {
          tell_object(me,HIG"\n���˼��ã�����Ҫ�졣\n"NOR);
          message_vision(HIC"\n$Nҡ��ҡͷ�������̾�˿�����\n"NOR,me); 
          tell_object(me,HBBLU"\n�ܿ�ϧ���㱾�γ���ԽŮ������ʧ�ܣ�\n"NOR);
          tell_object(me,HBBLU"��Ŀǰ�ľ�����" + me->query("combat_exp") + "������ʱ�����齣"+ NATURE_D->game_time() + "�����¼��\n"NOR);
          tell_object(me,HBBLU"�㽫�ڼ��24Сʱ������һ�λ��ᣡ��\n\n"NOR);
				
		 log_file("quest/yuenujian", sprintf("%s(%s) ��ԽŮ��ʧ��%d�Σ���ǰ����ֵkar(KAR)��%d(%d),��ǰ���ֵ��%d,��ǰ������ԣ�%d(%d),��ǰ���total��%d(%d),��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/ynj/fail"),
		 i,
		 me->query("kar"),
		 s,
		 j,
		 me->query("int"),
		 t,
		 total,
         me->query("combat_exp")));
        
          me->start_busy(1);
          me->add("quest/ynj/fail",1);
          me->set("quest/ynj/exp", me->query("combat_exp") );
          me->start_busy(1);
          me->set("quest/ynj/time",time());
        }
     
    return 1;
}

