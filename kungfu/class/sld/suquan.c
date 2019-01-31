// ����
// lane 2004.12.24 add ����

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
int ask_zhushao();
void destructing(object ob);



string ask_houshan();
string ask_me();
string ask_skill();
string ask_chansishou();
string ask_beauty();
string ask_shedujing();
string ask_beici();

int do_meihuo();

string ask_dulong();

int ask_gold();

void create()
{
	set_name("����", ({ "su quan","su" }));
	set("long", "����ģ��������ʮ�����꣬��һ����ò�ٸ���΢΢һЦ��������̬������\n������ƥ�����������̽����ķ��ˡ�\n");
	set("gender", "Ů��");
        set("title", "�����̽�������");
        set("age", 23);
        set("str", 22);
        set("int", 32);
        set("con", 22);
        set("dex", 38);
        set("per", 50);
        set("combat_exp", 125000000);
        set("shen", -10000);
        set("attitude", "peaceful");
        set("max_qi",29000);
        set("max_jing",8000);
        set("neili",29000);
        set("max_neili",29000);
        set("jingli",7800);
        set("eff_jingli",7800);
        set("jiali",200);
        set("score", 15000);
        set("yaoli_count",1);

	set_skill("force", 450);
	set_skill("dodge", 450);
	set_skill("parry",450);
	set_skill("hand",460);
	set_skill("chansi-shou", 460);
	set_skill("youlong-shenfa",450);
	set_skill("dulong-dafa",450);
	set_skill("dagger",480);
	set_skill("tenglong-bifa",480);
	set_skill("leg",460);
	set_skill("shenlong-tuifa",460);

	map_skill("force", "dulong-dafa");
	map_skill("dodge", "youlong-shenfa");
	map_skill("hand", "chansi-shou");
	map_skill("dagger","tenglong-bifa");
	map_skill("parry","tenglong-bifa");
	map_skill("leg","shenlong-tuifa");
	prepare_skill("hand","chansi-shou");

	set_temp("apply/damage", 88);
	set_temp("apply/dodge", 188);
	set_temp("apply/attack", 188);
	set_temp("apply/armor", 388);
	
	set("chat_chance_combat", 60);
	set("chat_msg_combat", ({
		(: perform_action, "hand.chansi" :) ,
		(: perform_action, "hand.tuxin" :) ,
		(: perform_action, "hand.luanwu" :) ,
		(: perform_action, "dagger.beauty" :) ,
		(: perform_action, "dagger.guifei" :) ,
		(: perform_action, "dagger.xiaolian" :) ,
		(: perform_action, "dagger.feiyan" :) ,
		(: exert_function, "wudi" :) ,
		(: exert_function, "shexin" :) ,
		(: exert_function, "pendu" :) ,
	}));      
	set("inquiry", ([
		"�ʽ�" : (: ask_gold :),
		"����" : (: ask_zhushao :),
		"�߶���" : (: ask_shedujing :),
		"zhushao" : (: ask_zhushao :),
		"�ɸ���": (: ask_houshan() :),
		"����ҩ��" : (: ask_me :),
		"�Ȼ����" : (: do_meihuo :),
		"��������" :(:ask_skill:),
		"���߲�˿��" :(:ask_chansishou:),
		"��������" :(:ask_beauty:),
		"Ҫ��" :(:ask_dulong:),
		"��ɱ����" :(:ask_beici:),

	]) );

	set("chat_chance", 3);
	set("chat_msg", ({
		"�������������������ذ����Ȼ�������Ͼ���������������\n",
	}));

	create_family("������",1, "��������");
	setup();
	carry_object("d/sld/npc/obj/skirt")->wear();
	carry_object(BINGQI_D("dagger/sld_bishou"))->wield();
}
string ask_shedujing()
{
	object me=this_player();
	object book;
	if (me->query("faminly/family_name")!="������" ||me->query("generation")>2)
	{
		command("�����ҽ��б���̫�ͣ����Ǻú�����������̫��������Ʋ��˶��ԣ������߻���ħ��\n");
		command("pat "+me->query("id"));
		return "�úøɣ��ҽ̵����ˣ�";
	}
	if (!me->query("quest/sld/dichuan"))
	{
		command("say ��������еմ�����!\n");
		return "�ߣ�\n";
	}
	if (me->query("party/gongji")<500)
	{
		command("say ������ɹ�������500��!\n");
		return "�ߣ�\n";
	}
	command("say ��Ȼ�����Ŭ����������һ���ؼ�������Ҫ�۳�������ɹ���ֵ500�㣬������ϧ������Դ��\n");
	me->add("party/gongji",-500);

	book=new("d/sld/obj/shedujing");
	book->move(me);
	command("blush");
	return "�Ȿ�������Ҫ�ú��ˣ���������������������㡣����ϰ�õ����������������͡�\n";

}
void attempt_apprentice(object ob)
{
       mapping myfam;

       myfam = (mapping)ob->query("family");
 	   if(!myfam || myfam["family_name"] != "������")
           command("say ��Ǳ��̵��ӣ�������ȥ�����ʹ��̰�.");
       else if(ob->query("shen",1) > -1500000)
           command("say �㻹�����ĺ�����,����1.5m������ȥ��ɱ�����׵����˰�");
       else if(ob->query_skill("dulong-dafa",1)<350)
       {
			command("say �����󷨲���250���������ҡ�");
            command("shake "+ob->query("id"));
	   }
	   else	if (!ob->query("quest/sld/dichuan"))
	   {
			command("say ��������еմ�����!\n");
			//return "�ߣ�\n";

	   }
       else
       {
            command("say �ðɣ��Ҿ����������ҵĵ��ӡ�");
			command("recruit " + ob->query("id"));
       }
	return;	
}
int accept_object(object me, object ob)
{
	object obj,su;
	su=this_object();
	if (ob->query("id")!="shenlong gou")
	{
	
		if( ob->query("weapon_prop/damage") >= 80){
		obj=unew(BINGQI_D("xtbs"));
		if(obj) {
			obj->move(me);
			tell_object(me,"����������ģ�����̫���ˣ��������ذ�׾��͸���ɣ�\n");
			tell_room(environment(me), "������" + me->name() + "һ������ذ�ס�\n");
		}
		else {
			tell_object(me,"����������ģ�����̫���ˣ��������������ģ�\n");
			me->add("shen", -(3000+random(1000)));
		}
		call_out("destructing", 0, ob);
		return 1;
		}
	}else { 
		if (me->query_temp("clgf/asksu1")
		&& objectp(present("shenlong gou",me)))
		{
			message_vision(HIC"$N���������صݸ�$nһ��"+ob->query("name")+"\n"NOR,me,su);
			ob->move(su);
			message_vision(HIC"$n�������ϸ����ָ�����ḧ��"+ob->query("name")+"��Ц��������һ���ñ�����\n������ô���ģ������������Ҳ�ò��ţ����͸����ˡ�\n"NOR,me,su);
			ob->move(me);
			me->set_temp("clgf/suok",1);
			message_vision(HIC"$nһ���֣�һ�ɴ�����������$N����һ��ɽ��ˮ��֮�ء�\n"NOR,me,su);

			me->move("d/sld/xfj");
		}
	}
	return 0;
}

void destructing(object ob)
{
	if(ob)
	destruct(ob);
}

int ask_zhushao()
{
	object me,ob,zs;
	mapping myfam;
	object* inv;
	int i;

	me = this_player();
	ob = this_object();
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "������") return 0;
	if(me->query("combat_exp") < 2000000) {
		command("say �����ڿɲ��ܸ�������Ŷ��");
		return 1;
	}

	inv = all_inventory(me);
	for(i=0; i<sizeof(inv); i++) {
		if(inv[i]->query("id")=="zhushao") {
			tell_object(me,"�㲻���Ѿ���������ô��\n");
			return 1;
		}
	}

	zs = new("d/sld/npc/obj/yushao");
	if (!zs)  return notify_fail("�쳣����\n");
	zs->set("owner",me);

	tell_object(me,"�ðɣ��Ҹ�������ڣ��ɲ�ҪŪ���ˡ�\n");
	tell_room(environment(me), "������" + me->name() + "һ���������ڡ�\n");
	zs->move(me);

	return 1;
}

string ask_me()
{
	object ob;
	mapping fam;
	if (!(fam = this_player()->query("family")) || fam["family_name"] != "������")
		return RANK_D->query_respect(this_player()) + "�뱾��������������֪�˻��Ӻ�̸��";

	if ( this_player()->query_temp("ask_slylj") )
		return "�ող��Ǹ������";
	ob=unew("/clone/book/slyaoli-book.c");

	if(!clonep(ob)) return "�������ˣ��Ǳ������Ѿ��������ˡ�";
	if(clonep(ob) && ob->violate_unique())
	{
		destruct(ob);
		return "�������ˣ��Ǳ������Ѿ��������ˡ�";
    }
	ob->move(this_player());
	this_player()->set_temp("ask_slylj", 1);
	message_vision("�����ӻ����ͳ�һ������ҩ���ݸ�$N��\n",this_player());
	return "�Ȿ�����Һ�½�������������ģ�����ȥ��Ҫ�ú��о�����";
}
/*
string ask_houshan()
{
	object me=this_player();
	if (me->query_temp("clgf",))
	{
	}
	int lvl = (int)me->query_skill("shenlong-yaoli", 1);
	if ( lvl < 120 ) return "�ɸ�����������ңʤ��,�������ҩ������120���㻹�����ʸ�ȥ��";
	if ( file_name(environment(this_object())) != this_object()->query("startroom"))
		return "���һ���������˵�ɡ�";
	tell_object(me, "�ǿ��Ǹ��õط���ɽ��ˮ�㣬�⾳�����Ȼ���ʵ��ˣ����Ҿʹ���ȥ�ɡ�\n");
	me->set_temp("clgf/clasksu",1);
	me->move("/d/sld/xfj");
	return "��һ�������ӡ�";
}*/

string ask_houshan()
{
	object me=this_player();
	int lvl = (int)me->query_skill("shenlong-yaoli", 1);

//	if (!me->query_temp("clgf/askhong"))
//	{
//		return "û�н������˭�����ܴ��ڴ˾�����\n";
//	}

	if ( lvl < 120 ) return "�ɸ�����������ңʤ��,�������ҩ������120���㻹�����ʸ�ȥ��";
	
	if ( file_name(environment(this_object())) != this_object()->query("startroom"))
		return "���һ���������˵�ɡ�";
	command("say �Ķ��Ǹ��õط���ɽ��ˮ�㣬�������ģ���������������õ����ڡ�\n");
	command("say ǰһ���Ӻͽ�����ס���Ķ������Ǻõط�......\n");

	tell_object(me, "������֪��Ϊʲô�������ƺ���Щ����֮����\n");
	
	me->set_temp("clgf/asksu1",1);
	me->delete_temp("clgf/askhong");
	return "��Ȼ���������ô��͸���ȥ�ҵ����������Ĵ�˵�еı����ɣ��ҵ����ҾͰѴ����ȥ��\n";
}

string ask_skill()
{
	object me=this_player();
	mapping myfam;
			
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "������") return 0;
	if(me->query_skill("tenglong-bifa",1)<100) return 0;
	if(me->query("sld/guifei") || me->query_skill("tenglong-bifa",1)<150)
		return "�㲻���Ѿ������������ô��";
	command("giggle");
	command("whisper "+getuid(me)+" ��ʵ�����������л��б�ľ�Ҫ֮���������������ġ�������");
	me->set("quest/sld/tlbf/guifei",1);
	tell_object(me,HIW"������������ָ�㣬��ס��ͷ�������������˹���������һ�еľ�Ҫ��\n"NOR);
	return "�����Ͼ��������ˣ������书�䲻�ع�����������ԽսԽǿ���������ҡ�";
}

int ask_gold()
{
	object me;
	int skill, gold;
	mapping myfam;
	me = this_player();
	skill = me->query_skill("dulong-dafa", 1);
	myfam = (mapping)me->query("family");

	if( !myfam || myfam["family_name"] != "������" ) {
		command("sneer "+(string)me->query("id"));
		command("say ��"+ RANK_D->query_respect(me) +"�����ú�ѽ���ǲ��ǿ����¼����ҽ̰���");
		return 1;
	}

	if( (int)me->query("sld_given") >= (int)me->query("age") ) {
		command("sigh "+(string)me->query("id"));
		command("say ����겻���Ѿ�����Ǯ�������������ɡ�");
		return 1;
	}

	if( (int)me->query("age") < 18 || skill < 100 ) {
		command("interest");
		command("say "+ RANK_D->query_respect(me) +"������ᣬ���ҽ̲��ã����ǰ���ѧ��ɡ�\n");
		return 1;
	}

	gold = 300000 + skill * 5000;
	if( 100 >= skill ) gold += gold/2;
	me->add("balance", gold);
	me->set("sld_given", (int)me->query("age"));
	command("say �ҽ̰���ʹ�ڳ�͢��Ҳ�Ǹ�����ݵ��ˣ��ʽ�Ȼ�����ѷ���");
	command("say �ҽ���" + MONEY_D->money_str(gold) + "�������Ǯׯ�����뵺���Ҫ�ú�Ϊ�ҽ̰��°���");
	return 1;
}
//��˿��
string ask_chansishou()
{
	object me=this_player();
	mapping myfam;
			
	myfam = (mapping)me->query("family");
	if(!myfam || myfam["family_name"] != "������") 
		return "����ҽ���Ա������������\n";
	if(me->query_skill("dulong-dafa",1)<250) 
		return "��Ķ����󷨵ȼ�����250���������ߺ�������\n";
	if(me->query("gender")!="Ů��") 
		return "��ֻϲ��Ů����ң���������ҽ���ȥ��\n";
	if(me->query("quest/sld/chss/pass"))
		return "��Ĳ�˿�ְ��ز����Ѿ������ô��\n";
	
	if (!me->query("quest/sld/dichuan"))
	{
		command("say ��������еմ�����!\n");
		return "�ߣ�\n";

	}
	if (me->query("party/gongji")<100)
	{
		command("say ������ɹ�������100��!\n");
		return "�ߣ�\n";
	}
	command("say ��Ȼ�����Ŭ��������Ҫ�۳�������ɹ���ֵ100�㣬������ϧ������Դ��\n");
	me->add("party/gongji",-100);

	
	command("giggle");
	command("smile");
	command("blush");
	command("smile");
	command("giggle");
	command("whisper "+getuid(me)+" ��ʵ���߲�˿�����л��б�ľ�Ҫ֮���������������ġ�������");
	me->set_temp("chansi/asksu",1);
	
	tell_object(me,HIW"������������ָ�㣬��ס��ͷ�������������˽��߲�˿����һ�еľ�Ҫ��\n"NOR);
	return "\n\n�����书����ʵ�����ܶ��似���Ǵӵ������������������Ҫ������������С�\n"+
		"\n������ܵ�ɽ�µ�������ȥ�۲�����ߵĶ������������ܶ�����߲�˿������͸����\n";
}

int do_meihuo()
{	
	object me = this_player();
	//int i=3+random(3);
	me->start_busy(1);
	if (me->query("family/family_name") != "������" ){
		command("say �㲻��������������ʿ����������\n");
		return 1;
	}

	if (me->query("family/generation")>2)
	{
		command("say ��Ƕ������ӣ�������������\n");
		return 1;
	}
	if (me->query_skill("tenglong-bifa",1)<450)
	{
		command("say �������ذ������450������Ҳѧ���ˣ�\n");
		return 1;
	}

    if (me->query("quest/sld/tlbf/meihuo/pass")){
		command("say ���Ѿ�����������⻹������������\n");        	
		return 1;				
	}
	if (me->query("gender")!="Ů��"){
		command("say ��������ذ���⹦���ҿ������Ǿ����ˣ���\n");        	
		return 1;				
	}
	if (time()-me->query("quest/sld/tlbf/meihuo/time")<86400){
		command("say ��Ҳ̫�ڿ����Ү����\n");        	
		return 1;				
	}
	if (me->is_busy())
	{
		command("say �������ŵ���Ҫ��ʲô��\n");
		return 1;
	}
	if (me->query_temp("tlbf/asksu"))
	{
		command("say ��������������̣�\n");
		return 1;
	}

	if (!me->query("quest/sld/dichuan"))
	{
		command("say ��������еմ�����!\n");
		return 1;

	}
	if (me->query("party/gongji")<100)
	{
		command("say ������ɹ�������100��!\n");
		return 1;
	}
	command("say ��Ȼ�����Ŭ��������Ҫ�۳�������ɹ���ֵ100�㣬������ϧ������Դ��\n");
	me->add("party/gongji",-100);

		    command("sigh ");
			command("����Ȼ��Ϊ�������ˣ�����....");
			command("sigh ");
			command("sigh ");
			command("blush ");
			message_vision(HIY"\n\n����һʱ�䲻֪��������ʲô�����Ϻ�һ�󣬰�һ���ƺ�������ŭ���ƺ�����������֮״��\n"NOR,me);
			command("sigh ");
			command("say ���Ȼ�֮�似��˵����Ҳûʲô��ֻ����ƾ��Ů�ı��ܰ��ˡ�\n");
		    command("say ������Ư����Ů��ʩչ����Ч���ܲ���\n");
			command("say ���������Ҿ�ָ����㣬�ܷ�������˾Ϳ����ˮƽ�ˡ�\n\n\n");
			me->set_temp("tlbf/asksu",1);
			message_vision(HIR"\n\n$N������������������̹�������ذ���Ȼ�ľ�����\n"NOR,me);
			me->start_busy(999);
			//remove_call_out("thinking");
			call_out("thinking",1,me);
		return 1;
			
}
//�Ȼ�
int thinking(object me)
{
  int i,j; 
  if(!me) return 0;
  i=random(me->query("kar"));
  j=random(10);
  me->set("quest/sld/tlbf/meihuo/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ��������ذ���Ȼ�ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  if(me->query_temp("canwu_meihuo")<(30+random(10)))
   {  
	  me->add_temp("canwu_meihuo",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����ʦ���Ľ�������ʦ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
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
      

	  tell_room(environment(me),HIC"\n"+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking");
	  call_out("thinking",3+random(3), me);

   } 
   else if (i>27
			&& j>7
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N�����͡�һ��Ц��������˵������ԭ�������������ѹ֡���������\n"NOR,me); 
		 message_vision(HIY"\n$N ���ڵ�֪��������Ϊ��������һ������Ĺ��򣬾�Ȼ�����˵����ѹֽ������˻���ˡ�\n"NOR,me); 
         message_vision(HIY"\n$N���»����������������������ڵ�����ذ�����Ȼ�İ��أ���\n"NOR,me); 
         log_file("quest/tlbfmeihuo", sprintf("%s(%s) ���ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ���������ذ���Ȼ�����İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/meihuo/fail"),
		 i,
		 j,
         me->query("combat_exp")));

		 me->set("quest/sld/tlbf/meihuo/time",time());
		 me->set("quest/sld/tlbf/meihuo/pass",1);
		 me->delete_temp("canwu_meihuo");
		 me->delete_temp("tlbf");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵�������������ˣ���ȻҪ����ȥչʾŮ���������Ҳ�����ˡ���\n"NOR,me); 
		 message_vision(HIY"\n��������ذ���Ȼ��������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/tlbfmeihuo", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�������ذ���Ȼ��������ǰ����ֵ��%d,��ǰ���ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/meihuo/fail",1),
		 i,
		 j,
         me->query("combat_exp")));
        
		 me->add("quest/sld/tlbf/meihuo/fail",1);
		 me->set("quest/sld/tlbf/meihuo/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_meihuo");
		 me->delete_temp("tlbf");
		 return 1;
   }

}
//��������

string ask_beauty()
{	
	object me = this_player();
	//int i=3+random(3);
	//me->start_busy(1);
	if (me->query("family/family_name") != "������" )
	{
		command("say �㲻��������������ʿ����������\n");
		return "";
	}
	if (me->query("family/generation")>2)
	{
		command("say ��Ƕ������ӣ�������������\n");
		return "";
	}
	if (me->query_skill("tenglong-bifa",1)<450)
	{
		command("say �������ذ������450������Ҳѧ���ˣ�\n");
		return "";
	}

    if (me->query("quest/sld/tlbf/beauty/pass")){
		command("say ���Ѿ����������������������ô����������������\n");        	
		return "";				
	}
	if (me->query("gender")!="Ů��"){
		command("say ��������ذ���⹦���ҿ������Ǿ����ˣ���\n");        	
		return "";				
	}
	if (time()-me->query("quest/sld/tlbf/beauty/time")<86400){
		command("say ��Ҳ̫�ڿ����Ү����\n");        	
		return "";				
	}
	if (me->is_busy())
	{
		command("say �������ŵ���Ҫ��ʲô��\n");
		return "��\n";
	}
	if (me->query_temp("tlbf/asksu"))
	{
		command("say ��������������̣�\n");
		return "��\n";
	}

	if (!me->query("quest/sld/dichuan"))
	{
		command("say ��������еմ�����!\n");
		return "�ߣ�\n";

	}
	if (me->query("party/gongji")<100)
	{
		command("say ������ɹ�������100��!\n");
		return "�ߣ�\n";
	}
	command("say ��Ȼ�����Ŭ��������Ҫ�۳�������ɹ���ֵ100�㣬������ϧ������Դ��\n");
	me->add("party/gongji",-200);

		    command("giggle ");
			command("���ǽ����������������似������Ѳ�.");
			command("giggle ");
			command("giggle ");
			command("giggle ");
			message_vision(HBMAG+HIW"$N��$n��������֮����������ذ������ʽ�ڻ��ͨ���ԡ��������С��ķ�ʽʩչ������\n"NOR,this_object(),me);
			message_vision(HBMAG+HIW"$N���е�ذ�׺�������������һ�С�������������\n"NOR,this_object());
			message_vision(HIR"$N�����м����������ȷ���ȹ���ȡ������߳���\n"NOR,this_object());

		    message_vision(HBMAG+HIW"$N����һ�С�С����¡�˳�ƶ�����\n"NOR,this_object());
			message_vision(HIC"$N�����м����Ų�˿�֡����߲�˿����\n"NOR,this_object());
			message_vision(HBMAG+HIW"$N����һ�С�������衹��\n"NOR,this_object());

			command("say ���������Ҿ�ָ���㣬�ܷ�������˾Ϳ����ˮƽ�ˡ�\n\n\n");
			me->set_temp("tlbf/asksu",1);
			message_vision(HIR"\n\n$N������������������̹�������ذ���Ȼ�ľ�����\n"NOR,me);
			me->start_busy(999);
			//remove_call_out("thinking_bt");
			call_out("thinking_bt",1,me);
		return "";
			
}


int thinking_bt(object me)
{
  int i,j; 
  if(!me) return 0;
  me->set("quest/sld/tlbf/beauty/time",time());
  if (me->query("kar")>30) 
  {
	  log_file("quest/bug", sprintf("%s(%s) ��������ذ����������ʱ��KAR�쳣����ǰ���飺%d�����䣺%d��kar:%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("combat_exp")),
		 me->query("age"),
		 me->query("kar"));
	  return 0;
  }
  i = 25;
  if(me->query("m-card-vip")) i =  22;
  if(me->query("y-card-vip")) i =  20;
  if(me->query("buyvip"))     i =  17;
  i=random(i);
  j=random(me->query("kar"));
  
  if(me->query_temp("canwu_bt")<(20+random(10)))
   {  
	  me->add_temp("canwu_bt",1);
	  switch (random(9))
	  {
		case 0:
			tell_object(me,HIG"\n����ϸ����ʦ���Ľ�������ʦ�������ڵ��ķ��˴�ӡ֤��ֻ���ö�Ŀһ��...\n"NOR);
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
      
	  tell_room(environment(me),HIC"\n"+me->query("name")+"��ɫƽ�ͣ���Ȼ���ң��ƺ���˼����ʲô...\n"NOR, ({}));

	  remove_call_out("thinking_bt");
	  call_out("thinking_bt",3+random(3), me);

   } 
   else if (i<3
			&& j>27
	   		&& random(me->query("int"))>40
			&& me->query("kar")<31)
 	{ 
        
         me->start_busy(3);     
         message_vision(HIY"\n$N�����͡�һ��Ц��������˵������ԭ�������������ѹ֡���������\n"NOR,me); 
		 //message_vision(HIY"\n$N ���ڵ�֪��������Ϊ��������һ������Ĺ��򣬾�Ȼ�����˵����ѹֽ������˻���ˡ�\n"NOR,me); 
         message_vision(HIY"\n$N���»����������������������ڵ�����ذ���⡾�������С��İ��أ���\n"NOR,me); 
         log_file("quest/tlbfbeauty", sprintf("%s(%s) ���ܳɹ�����%d�β��򣬻�Ե�ɺ��£��ɹ���������ذ���������о����İ��أ���ǰ����ֵ��%d,��ǰ���ֵ��%d,��������ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/beauty/fail"),
		 j,
		 i,
		 me->query("int"),
         me->query("combat_exp")));

		 me->set("quest/sld/tlbf/beauty/time",time());
		 me->set("quest/sld/tlbf/beauty/pass",1);
		 me->delete_temp("canwu_bt");
		 me->delete_temp("tlbf");
		 return 1;
     }
	 else {
	     message_vision(HIG"\n$N��̾һ�������������˵������������ذ�����ռ�������Ȼ����ѡ���\n"NOR,me); 
		 message_vision(HIY"\n��������ذ���������о�������ʧ�ܣ�\n"NOR,me); 
         log_file("quest/tlbfbeauty", sprintf("%s(%s) ʧ�ܣ���%d��ʧ�ܲ�������ذ���������о�������ǰ����ֵ��%d,��ǰ���ֵ��%d,��������ֵ��%d,��ǰ���飺%d��\n", 
         me->name(1),
         me->query("id"),
         me->query("quest/sld/tlbf/beauty/fail",1),
		 i,
		 j,
         me->query("int"),
         me->query("combat_exp")));
        
		 me->add("quest/sld/tlbf/beauty/fail",1);
		 me->set("quest/sld/tlbf/beauty/time",time());
		 me->start_busy(2);
		 me->delete_temp("canwu_bt");
		 me->delete_temp("tlbf");
		 return 1;
   }

}
//����������
string ask_dulong()
{
	object me,ob;
	int i,j;
	me=this_player();
	if (!me->query("quest/sld/dldf/dulong/start"))
	{
		command("say ����δ�˽������鶯��ʹ֮������Ҳ�״");
		return "��\n";
	}
	if (me->query_skill("qusheshu",1)<200)
	{
		command("say ��������Ҫ�ﵽ200��ɽ׶η�����ϰ��\n");
		return "";
	}
	if (me->query_skill("force",1)<450)
	{
		command("say �����ڹ��ﵽ450��ɽ׶η�����ϰ��\n");
		return "";
	}
	if (me->query("family/family_name")!="������")
	{
		command("say �㲢�������̵��ӣ�\n");
		return "";
	}
	if (time()-me->query("quest/sld/dldf/dulong/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�\n");
		return "";
	}
	if (me->query("quest/sld/dldf/dulong/pass"))
	{
		command("say ���Ѿ��⿪��������ˣ�\n");
		return "";
	}


	if (me->query("family/generation")>2)
	{
		command("say �㲢���������������ӣ��޷��������ž�����\n");
		return "";
	}
	
	if (!me->query("quest/sld/dichuan"))
	{
		command("say ����Ҵ����������еմ�����!\n");
		return "�ߣ�\n";

	}
	if (me->query_temp("quest/sld/dulong/asksu"))
	{
		command("say �Ҳ�������ȥ�ҽ���ô����ô����ȥ!\n");
		return "�ߣ�\n";

	}

	message_vision(HIY"������$N˵������ܲ�����Ȼ����ѵ�߹���������ô��������������򣬿����ǿ���֮�ģ���\n"NOR,me);
	command("say ���Ź����������������ĸ������Ҵ���������֪ͨһ������һ���ȥ�Ϳ���\n");
	command("blush "+me->query("id"));
	me->set_temp("quest/sld/dulong/asksu",1);
	return "";

}
//���̾���

string ask_beici()
{
	object me,ob;
	int i,j;
	me=this_player();
	if (me->query_skill("dagger",1)<350)
	{
		command("say �����ڹ��ﵽ350��ɽ׶η�����ϰ��\n");
		return "";
	}
		if (me->query_skill("dodge",1)<350)
	{
		command("say �����Ṧ�ﵽ350��ɽ׶η�����ϰ��\n");
		return "";
	}

	if (me->query("family/family_name")!="������")
	{
		command("say �㲢�������̵��ӣ�\n");
		return "";
	}
	if (me->query("family/generation")>2)
	{
		command("say �㲢���������������ӣ��޷��������ž�����\n");
		return "";
	}
	
	if (!me->query("quest/sld/dichuan"))
	{
		command("say ����Ҵ����������еմ�����!\n");
		return "�ߣ�\n";

	}
	if (time()-me->query("quest/sld/tlbf/beici/time")<86400)
	{
		command("say ������̫Ƶ���ˣ�\n");
		return "";
	}
	if (me->query("quest/sld/tlbf/beici/pass"))
	{
		command("say ���Ѿ��⿪��������ˣ�\n");
		return "";
	}

	command("consider ");
	message_vision(HIY"������$N˵������ܲ�������ذ����Ȼ���������ֵز��ˣ���\n"NOR,me);

	command("say ����������ذ�׾������Ǿ�ѧ���ʺ������鶯֮����ϰ��\n");
	command("say ���ű��̾���ʵ����͵Ϯ������\n");
	command("say ������ǰ�������������Ŀ����Է����ӶԷ��󱳴���շ�������ֱ�Ӵ�ɱ��\n");
	command("say ��Ȼ��Ҳ����ֱ�ӽ�ɱ�Է���������ͻϮ����Ѹ�ͣ�\n");
	command("say ��������Ȥ�Ҿͽ����ž����������㣡\n");
		  
	if (me->is_busy())
	{
	  command("say ������æµ��!\n");
	  return "";
	}
	me->start_busy(20);
	command("say ���������������������Ҫ�۳�������ɹ���ֵÿ��100�㣬���������û�ʸ�����ҡ�\n\n\n\n");

	if (me->query("party/gongji")<100)
	{
		command("say ������ɹ�������\n");
		return "";
	}
	command("say �ðɣ���Ȼ�����Ŭ�����Ҿ͸��������о��ϡ�\n");
    command("whisper "+me->query("id"));
	me->add("party/gongji",-100);
	
	i = 25;
		if(me->query("m-card-vip")) i =  22;
		if(me->query("y-card-vip")) i =  20;
		if(me->query("buyvip"))     i =  17;
		i=random(i);
		j=random(me->query("kar"));
		command("say ��������ô��\n");
		command("pat "+me->query("id"));
		if( i<5
			&& me->query("kar")<31
			&& j > 25 ) 
		{
			tell_object(me,HIC"\n�����˵�����������ָ�㣬�������͵Ϯ�Է��������ĵá�\n"NOR);
			
			tell_object(me,HIY"\n������ǧ����࣬�����������ű���͵Ϯ�ľ�����\n"NOR);

			me->set("quest/sld/tlbf/beici/pass",1);
			log_file("quest/sldbeici", sprintf("%8s(%8s) ʧ��%d�κ�ѧ������͵Ϯ����,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|������ǣ�%d��\n",
				me->name(1),me->query("id"), me->query("quest/sld/tlbf/beici/fail"),i,j,me->query("kar"),me->query_con(1)) );
			command("haha"+me->query("id"));		
			me->delete_temp("quest");
			me->start_busy(2);
			return "��ϲ���ܱ��̾����ɹ�!\n";
			
		}	
	   else
		{
			log_file("quest/slddulong", sprintf("%8s(%8s) ���ܱ��̾���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
				me->name(1),me->query("id"), me->query("quest/sld/tlbf/beici/fail"),i,j,me->query("kar"),me->query_con(1)) );
			
			tell_object(me,HIY"������������ָ�㣬���ǶԱ��̾����İ���ȫȻ����Ҫ�졣\n\n"NOR);
			command("sigh "+me->query("id"));
			command("disapp "+me->query("id"));
			me->add("quest/sld/tlbf/beici/fail",1);
			me->set("quest/sld/tlbf/beici/time",time());
			me->start_busy(2+random(3));
			me->delete_temp("quest");
			me->start_busy(2);
			return "�ǳ��ź����ܱ��̾���ʧ��"+me->query("quest/sld/tlbf/beici/fail")+"�Ρ�\n";
		}

	
}