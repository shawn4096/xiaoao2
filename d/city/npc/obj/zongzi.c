// zongzi.c
// update by renlai ��������

#define CHANCE 2   //��ͨ�����Ե�������Ʒ�İٷֱ�Ϊ 2%

#include <ansi.h>

inherit ITEM;

string long();

void create()
{
	int i,j, size;
	string name, id, id1,bonus;

	string *first_name=({HIR+"����",YEL+"����",HIY+"��ɳ"});
	string *first_id=({"hongzao","xianrou","dousha"});	
	string third_name="��"+NOR;
	string third_id="zong";
	string *bonuslist=({"combat_exp","gold","max_neili","pot ential"});

	size = sizeof(first_name);
	i = random(size);
	name = first_name[i];
	id = first_id[i];
	
	name += third_name;
	id1 = third_id;
	
	size=0;
	size= sizeof(bonuslist);
	j=0;
	j = random(size);
	bonus=bonuslist[j];	

	set_name(name, ({id+" "+id1,id,id1}));
	set_weight(500);
	set("bonus",bonus);
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", (: long :));
		set("unit", "ֻ");
		set("no_drop", 1);
		set("no_cun", 1);
		set("no_give", 1);        
		set("value", 2000);
		
	}
	setup();
}

void init()
{
	object me = this_player(), ob;

	if ( environment() == me ) {		
		add_action("do_eat", "fu");
	}

	//if ( !query("date_item")) return;

	//if ( query("owner") == getuid(me) )	return;

	//ob = find_player(query("owner"));

	//if ( ! ob) return;
/*
	if ( ob->query_temp("die_by_from") == me){
		ob->delete_temp("die_by_from");
		CHANNEL_D->do_channel( this_object(), "rumor",sprintf("%sŪ����һ��%s��", me->name(1), query("name")));
		set("owner", getuid(me));
		set("eat_time", uptime());
		
	}*/
	return;

}

string long()
{
	string str;

	str = query("name")+"("+capitalize(query("id"))+")\n";
	str += "һ��"+query("name")+"������(fu)�Ժ���";
	switch(query("bonus")) {
		case "combat_exp":	str +="����ʵս����";	break;
		case "gold":	    str +="�õ�����";	break;
		case "max_neili":	str +="�Ӵ�����";	break;
		case "potential":	str +="����Ǳ��";	break;
		default:		str +="һ��";		break;
	}
	str += "�Ĺ�Ч��\n";
	return str;
}

int do_eat(string arg)
{
	object me = this_player();
    object obj;
   int i, max, lvl;
	string str;
	if (!id(arg)) return 0;

	if ( me->is_busy() || me->is_fighting()) 
		return notify_fail("����æ���ء�\n");

	//if ( query("owner") != getuid(me))
	//	return notify_fail("���ʲô�ط��õ��ģ�\n");	
	
	
	//���ͨ����Ʒ by renlai
	
	
	//������˫��
	
	if(!mapp(me->query_conditions_by_type("db_exp"))) me->apply_condition("db_exp", 10000);
	   else me->add_condition("db_exp", 10000);	
	
	//�͵ȼ�����Ͳ��ɽ��׵����ݣ��ߵȼ��������
	
		if( me->query("combat_exp") > 5000000 ) {
			 
			message_vision(HIW"$N�շŽ�����һҧ��ֻ�������ԡ�һ����ҧ��һ�����ݣ�\n"NOR,me);
			obj = new("/clone/zhiye/othermaterial");			
			
			obj->set_level(6,random(2)?1:2);
			obj->move(me);			
			obj->set("date_item",1);
			CHANNEL_D->do_channel( this_object(), "rumor",sprintf("���˿���%s��������Ե���һ��%s��", me->name(1), obj->query("name")));
			message_vision(HIR"$N������ġ�����ó�������һ����ԭ���ǿ�"HIC"����"HIR"��\n"NOR,me);
			destruct(this_object());
			log_file("job/shijian", sprintf("%8s%-10sʳ�õõ�%6s��\n",me->name(1),"("+getuid(me)+")",obj->query("name")), me);
			return 1;
		}	

		str = HIW"$N����һ��"+query("name")+HIW"����ʱ���û���Ϊ֮һ��������";
		switch(query("bonus")) {
		case "combat_exp":			
				i = 10000 + random(2000);
			    me->add("combat_exp", i);
			    log_file("job/shijian", sprintf("%8s%-10sʳ��%6s���õ�%4d�㾭�顣\n",me->name(1),"("+getuid(me)+")",query("name"),i), me);
			    str += chinese_number(i)+"��ʵս���顣\n"NOR;
			break;
		case "gold":
			i = 1000000;
			me->add("balance",1000000);
			str += MONEY_D->money_str(1000000)+"���ƽ�\n"NOR;
			break;
		case "max_neili":
			i = random(50) + 50;
			max = (me->query_skill("force")-me->query_temp("apply/force")) * 8 + me->query("combat_exp") / 1000;
			if ( (me->query("max_neili") - 100 ) < max )
				me->add("max_neili", i);
			str += chinese_number(i)+"�����������\n"NOR;
			break;
		case "potential":
			i = 100000;
			me->add("potential", i);			
			str += chinese_number(i)+"��Ǳ�ܡ�\n"NOR;
			break;
		default :
			   i = 10000 + random(2000);
			    me->add("combat_exp", i);
			    log_file("job/shijian", sprintf("%8s%-10sʳ��%6s���õ�%4d�㾭�顣\n",me->name(1),"("+getuid(me)+")",query("name"),i), me);
			    str += chinese_number(i)+"��ʵս���顣\n"NOR;
	}
	
	message_vision(str, me);
	"/adm/daemons/emoted"->do_emote(me,"taste");
	if (query("date_item")) CHANNEL_D->do_channel( this_object(), "rumor",sprintf("���˿���%s������һ��%s��", me->name(1), query("name")));
    destruct(this_object());	
	return 1;
}

