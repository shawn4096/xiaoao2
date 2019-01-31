// hetaichong.c (kunlun)
// By Spiderii ��ʱ�رգ�����ͽ
#include <ansi.h>

inherit NPC;
inherit F_MASTER;
string ask_me();
string ask_fail();
string ask_qinji();
string ask_job();
int accept_object(object who,object obj);
string ask_feipu();

#include <job_mul.h>
//#include "d/kunlun/npc/jianxi.h"

string *names = ({
"/d/fairyland/shanlu1",	"/d/fairyland/shanlu2",	"/d/fairyland/hmzhuang",
"/d/fairyland/dating",	"/d/fairyland/nuange",	"/d/fairyland/houyuan",
"/d/fairyland/lggong",	"/d/fairyland/shanxi",	"/d/fairyland/xuanya",
"/d/group/entry/klclin1",
"/d/kunlun/klshanlu","/d/kunlun/shanmen",
"/d/kunlun/shanlu01",	"/d/kunlun/shanlu02",	"/d/kunlun/shanlu03",
"/d/kunlun/shanlu04",		"/d/kunlun/guangchangw",	"/d/kunlun/guangchang",
"/d/kunlun/guangchange",	"/d/kunlun/pingfeng",	"/d/kunlun/qianting",
"/d/kunlun/keting2",	"/d/kunlun/elang01",	"/d/kunlun/wlang01",
"/d/kunlun/keting1",	"/d/kunlun/shilu1",	"/d/kunlun/shufang",
"/d/kunlun/jingxiushi",	"/d/kunlun/huayuan1",	"/d/kunlun/lang",
"/d/kunlun/lang2",	"/d/kunlun/liangong",	"/d/kunlun/lang1",
"/d/kunlun/sanshengtang",	"/d/kunlun/gate",	"/d/kunlun/shilu2",
"/d/kunlun/jiuqulang2",	"/d/kunlun/shanlin1","/d/kunlun/shanlin2",
"/d/kunlun/shanlin3",	"/d/kunlun/houyuan",	"/d/kunlun/fufengshan",
"/d/kunlun/jiuqulang1",	"/d/kunlun/tieqinju","/d/kunlun/shiqiao"
});


void create()
{
	set_name("��̫��", ({ "he taichong", "he" }));
	set("title", "����������");
        set("nickname", MAG"��������"NOR);
	set("long",
		"���������������š����ｭ��������������̫�塣\n"
		"��Ȼ����Ѵ󣬵���Ȼ���ó�������ʱӢ��������\n");
	set("gender", "����");
	set("age", 40);
	set("attitude", "heroism");
	set("shen_type", -1);
	set("str", 25);
	set("int", 25);
	set("con", 25);
	set("dex", 25);

	set("max_qi", 13500);
	set("max_jing", 6000);
	set("neili", 29000);
	set("max_neili", 29000);
	set("eff_jingli", 6000);
	set("jiali", 200);
	set("combat_exp", 12500000);
	set("score", 4000);
	set("qinji-book",1);
	set_skill("art", 200);
    set_skill("literate", 250);
	set_skill("force", 460);
	set_skill("xuantian-wuji", 460);
	set_skill("dodge", 460);
	set_skill("taxue-wuhen", 460);
	set_skill("parry", 460);
	set_skill("sword", 480);
	set_skill("liangyi-jue", 160);
	set_skill("liangyi-jian", 480);
	set_skill("cuff", 460);
	set_skill("zhentian-quan", 460);
	set_skill("strike", 460);
	set_skill("kunlun-zhang", 460);
	map_skill("strike", "kunlun-zhang");
	map_skill("force", "xuantian-wuji");
	map_skill("dodge", "taxue-wuhen");
	map_skill("cuff", "zhentian-quan");
	map_skill("parry", "liangyi-jian");
	map_skill("sword", "liangyi-jian");
	set("chat_chance_combat", 50);
	set("chat_msg_combat", ({
  		(: perform_action, "sword.feipu" :),
		(: perform_action, "sword.jinzhen" :),

  		(: perform_action, "sword.feihua" :),
		(: perform_action, "sword.duanyun" :),
		(: exert_function, "wuji" :),			
  		(: perform_action, "dodge.taxue" :),
	}));
	prepare_skill("cuff", "zhentian-quan");
	prepare_skill("strike", "kunlun-zhang");

    create_family("������", 3, "������");
	set("class", "taoist");

	set("inquiry", ([
		"�ķ�" : (: ask_me :),
		"�ټ����ż���" : (: ask_qinji :),
		"����" : (: ask_fail :),
		"fail" : (: ask_fail :),
		"���ɷ��پ���" : (: ask_feipu :),

		"����" : (: ask_job :),
		"job" : (: ask_job :),

	]));

	set("book_count", 1);
	set("ding_count", 18);

	setup();
	carry_object(BINGQI_D("changjian"))->wield();
	carry_object("/d/kunlun/obj/pao2.c")->wear();
}
void attempt_apprentice(object ob)
{
        if(ob->query("gender")=="Ů��"){
 	    command("haha");
	    command("say "+RANK_D->query_respect(ob)+"�Ϸ�ɲ�����Ů���ӣ���ȥ���ҷ���ȥ�ɡ�");
	    return;
	}
        if(ob->query("appren_hezudao", 1) == 1) {
  	   command("say "+RANK_D->query_respect(ob)+"���ҿ������Ц��������ɱ���ˡ�");
	   return;
	}
	if(ob->query_skill("xuantian-wuji",1) < 300){
  	   command("hmm");
	   command("say "+RANK_D->query_respect(ob)+"��������޼���̫�����300���ҿɲ������㡣");
 	   return;
	}
	if(ob->query_skill("zhentian-quan",1) < 300){
  	   command("hmm");
	   command("say "+RANK_D->query_respect(ob)+"�������ȭ̫�����300���ҿɲ������㡣");
 	   return;
	}

	if(ob->query_skill("taixue-wuhen",1) < 300){
  	   command("hmm");
	   command("say "+RANK_D->query_respect(ob)+"���̤ѩ�޺�̫�����300���ҿɲ������㡣");
 	   return;
	}
	command("say �ðɣ��ұ������㣬ֻ����Ͷ��������֮����ð���ѧ�ա�");
	command("recruit " + ob->query("id"));
	ob->set("title","�����ɵ��Ĵ�����");

}
string ask_me()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";

        if(this_player()->query("gender")!="Ů��" && this_player()->query("per") < 23)
   	   return "�����ľ����������";

		ob = unew("/d/kunlun/obj/force-book.c");
        if(!clonep(ob)) return "�������ˣ������ľ��ѱ���ʦ�������ˡ�";
        if(clonep(ob) && ob->violate_unique()){
               destruct(ob);
  	       return "�������ˣ������ľ��ѱ���ʦ�������ˡ�";
        }
		ob->move(this_player());
		return "�������б����ķ��������й����������ģ����û�ȥ�ú����У��пն�������Ŷ";
}
string ask_qinji()
{
	mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "������")
	   return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";  
		
		if (this_object()->query("qinji-book")<1)
		{
			 return "�������ˣ������ľ��ѱ���ʦ�������ˡ�";
		}
		if (this_player()->query_skill("xuantian-wuji",1)<200)
		{
			return RANK_D->query_respect(this_player())+ "��������޼�����200�����������޷�������\n";  
		}
		this_object()->add("qinji-book",-1);
		ob = unew("/d/kunlun/obj/string-book3.c");     
		ob->move(this_player());

		return "�������б����ټ����ż��ɡ������û�ȥ�ú����У��пն�������Ŷ";
}
//����׷ɱ��ϸ����

string ask_ding()
{
        mapping fam;
	object ob;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "������")
	    return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";
		
	if(this_player()->query_skill("mantian-huayu",1) < 60)
            return "�������ԸΪʦ��Ч����������ƽʱһ�����࣬����ȥ��";
		   
	if(present("sangmen ding", this_player()) )
	    return RANK_D->query_respect(this_player())+"���������ϲ���������ô����Ҫ�ˣ�";

    if (query("ding_count") < 1)
	    return "ɥ�Ŷ��Ѹ�������ȥ׷ɱ��ϰ֮���ˣ���Ͳ���ȥ�ˡ�";
	add("ding_count", -1);
	this_player()->set_temp("kunlun/ding",1);
	ob = new(BINGQI_D("sm_ding"));
	ob->move(this_player());
	return "�������ԸΪʦ��Ч����������ƽʱһ�����࣬���ɥ�Ŷ������ȥ�ɡ�";
}

string ask_su()
{
        mapping fam;

	if (!(fam = this_player()->query("family"))
	 || fam["family_name"] != "������")
	    return RANK_D->query_respect(this_player())+ "�뱾��������������֪�˻��Ӻ�̸��";
		
	if(this_player()->query_temp("kunlun/ding",1))
            return "�㻹����������ʲô��������ȥ׷��ϰ֮";
	    return "��ϰ֮��һﾹȻ��͵�����ɵ������񽣣����ɵ��ӱص�����׷ɱ��";
}

//����׷ɱ��ϸjob

string ask_job()
{
	object ob, me, ling;
	object jianxi;
	mixed objwhere;
	string str,stw;
	me=this_player();
	ob = this_object();
	
	ling = present("zhusha ling", me);
    
	if(me->query("family/family_name")!="������") 
           return "�㲻�������ص��ӣ��������ɶ�Թ��Ͳ�Ҫ�����ˡ� ";

	if (me->query_temp("kl/zhuisha"))
		return "�Ҳ�������ȥ׷ɱһ��͵ѧ�������似�ļ�ϸ"+me->query_temp("kl/zhuisha/name")+"��ô����\n";

	if ((int)me->query("combat_exp") < 100000)
		return "���书δ�ɣ���ôΣ�յ������Ǳ����ˣ�\n";

	if (me->query("job_name") == "����׷ɱ��ϸ")
		return "�������׷ɱ��ϸ�������Լ�ȥ��ϰ�书ȥ�ɣ�";

	if(me->query_condition("job_busy"))
		return "��������æ�������������أ�";
	if(me->query_condition("klzsjob_busy"))
		return "��������æ����׷ɱ��ϸ�����أ�";

	if(me->query_temp("quest/busy")) //added by tangfeng ��quest��ͻ
		return "����������û�и���������㻹���ȴ����������������˵�ɡ�";
    
	//�����ϸ����
    jianxi=new("/d/kunlun/npc/jianxi");
	jianxi->set("long",jianxi->query("long")+"\n����"+me->query("name")+"����׷ɱ�������ɼ�ϸ��\n"NOR);
	jianxi->set("owner",me->query("id"));
	//��ֵjianxi
	
	jianxi->do_clone(jianxi, me);
	//�����ϸλ��
	//str=names[random(sizeof(names))];
	
	objwhere = names[random(sizeof(names))];

	//objwhere =load_object(str);
	if (!objwhere) objwhere = names[random(sizeof(names))];
	
	jianxi->move(objwhere);
	
	command("nod "+me->query("id"));
	message_vision(HIY"$N��������ã����������Щ�������µ��ӽ���������͵ѧ�Ҵ������书�����¾����ܰ��ݣ�\n"NOR,me);
	command("say �յõ����е����鱨��������"+objwhere->query("short")+"һ������һ����ϸ��\n");
	command("say �������ˣ��˼�ϸ�����ֽС�"+jianxi->query("name")+"("+jianxi->query("id")+")�����ɱ����������ˣ�\n");
	command("say ��������ʱ�������ձ����ֲ���ã�Ӧ�þ�������ɽ���������ȥ��أ���Ҫ���飡\n");
	command("say ����ʲô���ɵģ�ץ������ֱ�Ӿ͵ش���������ͷ���ң�����Ч�ȣ�\n");
	
	me->set_temp("kl/zhuisha/place",objwhere->query("short"));
	me->set_temp("kl/zhuisha/id",jianxi->query("id"));
	me->set_temp("kl/zhuisha/name",jianxi->query("name"));
	me->set_temp("kl/zhuisha/time",time());

	me->apply_condition("hs_job", 30 + random(5));
	me->apply_condition("job_busy", 30);

	
	return "��֪���˹����������ǧ��ҪС�ģ���ȥ��أ�\n";
	
}
int accept_object(object who,object obj)
{
	object obb;
	int exp,pot,exprelife,expdb;
	string msg;
	exp=100+random(20);
	pot=50+random(10);
	exprelife=0;
	expdb=0;
//�����ݲ�ͬ������ͬ
	
	if(who->query("buyvip") )
       exp = exp + exp* 20/ 100;
	else if(who->query("y-card-vip"))
       exp = exp + exp * 10 / 100;
	else if(who->query("m-card-vip"))
       exp = exp + exp * 5 / 100;
	


	obb=obj->query("kill_by");
	if (obj->query("name")==who->query("kl/zhuisha/name")
		||obb->query("id")==who->query("id"))
	{
		command("haha "+who->query("id"));
		command("say ���ܽ�"+obj->query("victim_name")+"�����ϸ����ɱ�ˣ��Һܸ��ˣ�\n");
		command("pat "+who->query("id"));
		command("say ��˵��������书���������Һܿ����㣡\n");
		command("say ������ȥ�ú���Ϣ�ɣ�\n");
		destruct(obj);
		message_vision(RED"\n\n��̫��˦�ֽ������ͷ�����پֶ�¥������˦�����������\n"NOR,who);
	
		msg=YEL"��̫���ͷ���������Ĵָ�����ָ���$N"+exp+"�㾭��ֵ��"+pot+"��Ǳ�ܣ�\n"NOR;
		//����exp
		if(who->query("relife/exp_ext"))
		{
           exprelife=exp*(int)who->query("relife/exp_ext",1) / 20;
		   msg+=YEL"��������ڼ䣬$N�ֶ�����"+chinese_number(exprelife)+"�㾭��ֵ��\n"NOR;

        }

        if(who->query_condition("db_exp")){  
            expdb=exp;
            msg += HIY + "˫�����齱���ڼ䣬�����صõ���" + HIW + chinese_number(expdb) + HIC + "��" + HIM + "���飡\n"NOR;
        }		
		//����
		exp=exp+exprelife+expdb;

		if(who->query("combat_exp") > 75000000){
            exp =  exp * 5 /100;
            tell_object(obj,"������Լ����������������ѧ���о��Ѿ������˾ٲ�Ω��ĳ̶ȣ��ƺ����ǽ�����˵�ġ�"+HIG+"��ѧ��"+NOR+"����\n");
        }
	//����
		who->add("combat_exp",exp);
		who->add("potential",pot);
		who->add("job_time/����׷ɱ",1);
		who->set("job_name","����׷ɱ��ϸ");
		message_vision(msg,who);

		if (random(who->query("job_time/����׷ɱ"))>800
			&&random(who->query("kar"))>25)
		{
			message_vision(HIG"\n��̫����������Ц��˵��������������޲����������������Ϊ���ɵմ����ӡ���\n"NOR,who);
			who->set("title","�����ɵմ�����");
			who->set("quest/kl/dichuan",1);
		}
		who->apply_condition("job_busy",3);
		who->apply_condition("klzsjob_busy",3);
		who->delete_temp("kl/zhuisha");
	}	

	return 1;
}
int ask_fail()
{
	object me;
	mapping ob;
	string name;
	me=this_player();
	command("heng "+me->query("id"));
	command("angry "+me->query("id"));
	if (!me->query_temp("kl/zhuisha"))
	{
		command("say ��ʲô��û����Ϲ����ʲô��\n");
		return 1;
	}

	command("say ��Ȼ���겻�ɾ���ʱ��ȥЪϢȥ�ˣ������Ǽ�ס���ˡ�\n");
	me->delete_temp("kl/zhuisha");
	me->apply_condtion("job_busy",4);

	return 1;
}

string ask_feipu()
{
	object me;
	int i,j;
	me=this_player();
	if (me->query("family/family_name")!="������")
	{
		return "��Ĳ��������ɣ��ѵ�������ô����\n";
	}
	if (me->query_skill("liangyi-jian",1)<250)
	{
		return "������ǽ��ȼ�����250��������Ҳû�ã�\n";
	}
	if (me->query("quest/kl/lyj/feipu/pass"))
	{
		return "������ǽ������ɷ����Ѿ��⿪�ˡ���\n";
	}
	if (time()-me->query("quest/kl/lyj/feipu/time")<86400)
	{
		return "������̫Ƶ���ˣ�����������\n";
	}

	message_vision(HIC"$N����Ŀ���$n������˵���������ɵ����ǽ������Ľ������飬���������ɶ���̫��ͬ��\n"
						"���Ȼ������˳̶ȣ��Ҿʹ��������а��ɷ��ٵİ��أ��Ҹ�����ʾһ�飬�����Լ��������ˡ�\n"+
				   HIR"\n\n\n$N�������һ������������Ծ�����ٲ�к�£�����$n�����ҡ\n"NOR,this_object(),me);
	
 
    i = 20;
      if(me->query("m-card-vip")) i =  18;
      if(me->query("y-card-vip")) i =  15;
      if(me->query("buyvip"))     i =  10;
      i=random(i);
	j=random(me->query("kar"));
	command("say �㿴����ô��\n");
	command("pat "+me->query("id"));
	if( i<5
		&& me->query("kar")<31
		&& j >= 25 ) 
	{
		tell_object(me,HIY"\n�����˵ĺ�̫�������ָ�㣬�����������Լ��������ǽ��������ĵã�����ӡ�ա�\n"NOR);
		tell_object(me,HIG"\n�㽣�����������糤����ӣ����ϲ�����һ���ֽ��м�Ϊ������ʽ������ʶ�ĳ��С�\n"
			             +"��ʽ���Ʒ��������������ʽ���Ѿ���Ȼ���أ��������������಻����\n"
						 +"���������������Ű��ɷ��ٵ����÷��š����д�ϲ��\n"NOR);
		me->set("quest/kl/lyj/feipu/pass",1);
		log_file("quest/lyjfeipu", sprintf("%8s(%8s) ʧ��%d�κ�ѧ�����ɷ���,�����ڻ��ͨ�������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feipu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		command("haha"+me->query("id"));		
		
		return "��ϲ���ܰ��ɷ��پ����ɹ�!\n";
		
	}	
   else
	{
		log_file("quest/lyjfeipu", sprintf("%8s(%8s) ���ܰ��ɷ��پ���ʧ��%d�Σ��������iȡֵ��%d|�����Դjȡֵ��%d|��ǰ��Դȡֵ��%d|���飺%d��\n",
			me->name(1),me->query("id"), me->query("quest/kl/lyj/feipu/fail"),i,j,me->query("kar"),me->query("combat_exp")) );
		
		tell_object(me,HIY"�����˺�̫���ָ�㣬���Ƕ����ǽ������ɷ��ٵİ���ȫȻ����Ҫ�졣\n\n"NOR);
		command("sigh "+me->query("id"));
		command("disapp "+me->query("id"));
		me->add("quest/kl/lyj/feipu/fail",1);
		me->set("quest/kl/lyj/feipu/time",time());
		me->start_busy(1+random(3));
		
		return "�ǳ��ź��������ǽ�֮���ɷ���ʧ��"+me->query("quest/kl/lyj/feipu/fail")+"�Ρ�\n";
	}


}