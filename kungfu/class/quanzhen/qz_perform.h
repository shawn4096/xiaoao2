// quanzhen_perform.h
// 全真教perform
// by sohu@xojh 

//#include <ansi.h>

/*inherit F_DBASE;
inherit F_SSERVER;
//全真七子解密内容
set("sae",1);
//this_object()->set("quest/qz/qzjf/qixing/pass",1);
set("quest/qz/htz/sanhua/pass",1);
set("quest/qz/hzt/chongyang/pass",1);
set("quest/qz/qzjf/jianjue/pass",1);
set("quest/qz/qzjf/lian/pass",1);
set("quest/qz/xtg/daojue/pass",1);
set("quest/qz/xtg/wuqi/pass",1);
set("quest/qz/xtg/yusuo/pass",9);*/

/*
int perexert()
{
	object weapon, me;
	me = this_object();
	weapon = me->query_temp("weapon");
	if(me->is_busy()) return 0;
	call_out("cont_per", 1, me, weapon);
	return 1;
}

void cont_per(object me, object weapon)
{
	int i;
	if (!me->is_fighting()) return;
	
	if(!me->query_temp("xtg/wuqi")||!me->query_temp("xtg/daojue")) {
		command("exert wuqi");
		command("exert daojue");
		return;
	} else {	
		
		switch(random(5)) {
        case 0:
			if (!weapon) command("wield sword");
			command("perform strike.haorao");
			break;
        case 1:
			if (!weapon) command("wield sword");
			else command("perform leg.lianhuan");
			break;
        case 2:
			if (weapon) weapon->unwield();
			me->prepare_skill("strike");
			me->prepare_skill("strike", "haotian-zhang");
			command("perform strike.pobing");
			if (weapon) weapon->wield();
			break;
        case 3:
			if (weapon) weapon->unwield();
			me->prepare_skill("strike");
			me->prepare_skill("strike","tanzhi-shentong");
			command("perform strike.juding");
			break;
        case 4:
			if (weapon) weapon->unwield();
			me->prepare_skill("finger");
			me->prepare_skill("hand");
			me->prepare_skill("leg", "xuanfeng-tui");
			me->prepare_skill("strike","luoying-zhang");
			command("perform pikong");
			if (weapon) weapon->wield();
			break;
	}}
	call_out("cont_per", 2, me, weapon);
}
*/