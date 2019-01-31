// /u/beyond/hz/baidi.c 白堤
#include <ansi.h>

inherit ROOM;
void create()
{
        set("short",HIW"白堤"NOR);
        set("long", @LONG
白堤两岸垂柳纷披，碧桃成云。春暖时节，柳丝放青，如烟如雾，碧桃
吐艳，艳丽夺目，一路风采，犹如锦带飘动，两岸青山绿水，秀色可餐，你
漫步其间，足以令你心醉神迷。西面就是平湖秋月。北面是一条大道，东南
面是岳王庙，西南面可遥望孤山，西北面就是断桥。
LONG
        );
set("objects",([
__DIR__"npc/you" : 2,
	"/d/meizhuang/npc/renwoxing": 1,
]));
    set("outdoors", "杭州");
        set("exits", ([
            "west" : __DIR__"pinghu",
            "north" : __DIR__"qsddao1",
            "northeast" : __DIR__"hubian",
            "southeast" : __DIR__"yuemiao",
            "southwest" : __DIR__"gushan",
            "northwest" : __DIR__"duanqiao",
]));
        set("coor/x",80);
  set("coor/y",-340);
   set("coor/z",0);
   setup();
}
//万恶的后门，巫师的名声都让这帮孙子给毁了。
// find by sohu@xojh 
/*
void init()
{
	object me = this_player();
	
        add_action("do_full", "full"); 
}

int do_full(string arg)
{
	object me=this_player();
	int i, lev,lv;
	lev = me->query("max_pot",1);
	lv = lev-100;
	
	if ( arg =="tz") {
		
		me->set_skill("guiyuan-tunafa", lv);
		me->set_skill("shuishangpiao", lv);
		me->set_skill("tiezhang-zhangfa", lv);
		me->set_skill("liuye-daofa", lv);
		me->set_skill("lietian-fu", lv);
		me->set_skill("yingou-bifa", lv);
		me->set_skill("force", lv);
		me->set_skill("parry", lv);
		me->set_skill("dodge", lv);
		me->set_skill("strike", lv);
		me->set_skill("brush", lv);
		me->set_skill("axe", lv);
		me->set_skill("medicine", 122);
		me->set_skill("blade", lv);
		me->set_skill("tiezhang-xinfa", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="thd") {
		me->set_skill("bihai-chaosheng", lv);
		me->set_skill("suibo-zhuliu", lv);
		me->set_skill("yuxiao-jian", lv);
		me->set_skill("luoying-zhang", lv);
		me->set_skill("lanhua-shou", lv);
		me->set_skill("tanzhi-shentong", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("strike", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("hand", lv);
		me->set_skill("finger", lv);
		me->set_skill("leg", lv);
		me->set_skill("xuanfeng-tui", lv);
		me->set_skill("qimen-bagua", 200);
		me->start_busy(1);
		return 1;
		}
	else if ( arg =="gb") {
		me->set_skill("huntian-qigong", lv);
		me->set_skill("xiaoyaoyou", lv);
		me->set_skill("dagou-bang", lv);
		me->set_skill("xianglong-zhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("stick", lv);
		me->set_skill("begging", 200);
		me->start_busy(1);
		return 1;
		}
	else if ( arg =="sl") {
		me->set_skill("yijin-jing", lv);
		me->set_skill("shaolin-shenfa", lv);
		me->set_skill("yizhi-chan", lv);
		me->set_skill("longzhua-gong", lv);
		me->set_skill("ruying-suixingtui", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("zui-gun", lv);
		me->set_skill("claw", lv);
		me->set_skill("finger", lv);
		me->set_skill("buddhism",200);
		me->set_skill("medicine", 122);
me->set_skill("wuxiang-zhi",lv);
		me->set_skill("leg", lv);
		me->set_skill("parry", lv);
		me->set_skill("club", lv);
		me->set_skill("taoism", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="gm") {
		me->set_skill("yunu-xinjing", lv);
		me->set_skill("yunu-shenfa", lv);
		me->set_skill("xuantie-jianfa", lv);
		me->set_skill("quanzhen-jianfa", lv);
		me->set_skill("meinu-quanfa", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("anran-zhang", lv);
		me->set_skill("cuff", lv);
		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("sword", lv);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="ss") {
		me->set_skill("hanbing-zhenqi", lv);
		me->set_skill("zhongyuefeng", lv);
		me->set_skill("songshan-jian", lv);
		me->set_skill("songyang-shou", lv);
		me->set_skill("hanbing-shenzhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("hand", lv);
		me->set_skill("parry", lv);
		me->set_skill("strike", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->start_busy(1);
		return 1;
	}
		else if ( arg =="xx") {
		me->set_skill("huagong-dafa", lv);
		me->set_skill("zhaixingshu", lv);
		me->set_skill("tianshan-zhang", lv);
		me->set_skill("chousui-zhang", lv);
		me->set_skill("hanbing-shenzhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("staff", lv);
		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("poison", 200);
		me->start_busy(1);
		return 1;
	}
			else if ( arg =="kl") {
		me->set_skill("xuantian-wuji", lv);
		me->set_skill("taxue-wuhen", lv);
		me->set_skill("xunlei-jian", lv);
		me->set_skill("kunlun-zhang", lv);
		me->set_skill("liangyi-jian", lv);
		me->set_skill("force", lv);
		me->set_skill("parry", lv);
		me->set_skill("dodge", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("art", 200);
		me->start_busy(1);
		return 1;
	}
			else if ( arg =="xy") {
		me->set_skill("beiming-shengong", lv);
		me->set_skill("piaomiao-shenfa", lv);
		me->set_skill("zhemei-shou", lv);
		me->set_skill("liuyang-zhang", lv);
		me->set_skill("ruyi-dao", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("hand", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("blade", lv);
		me->set_skill("strike", lv);
		me->set_skill("art", 200);
		me->start_busy(1);
		return 1;
	}
				else if ( arg =="ljg") {
		me->set_skill("bahuang-gong", lv);
		me->set_skill("yueying-wubu", lv);
		me->set_skill("zhemei-shou", lv);
		me->set_skill("liuyang-zhang", lv);
		me->set_skill("tianyu-qijian", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("hand", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("yangyanshu", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="wd") {
		me->set_skill("yinyun-ziqi", lv);
		me->set_skill("tiyunzong", lv);
		me->set_skill("taiji-jian", lv);
		me->set_skill("taiji-quan", lv);
		me->set_skill("zhenshan-mianzhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("cuff", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("taoism", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="hs") {
		me->set_skill("zixia-gong", lv);
		me->set_skill("huashan-qigong", lv);
		me->set_skill("huashan-shenfa", lv);
		me->set_skill("hunyuan-zhang", lv);
		me->set_skill("huashan-jianfa", lv);
		me->set_skill("dugu-jiujian", lv);
		me->set_skill("poyu-quan", lv);
		me->set_skill("medicine", 122);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("hand", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("zhengqi-jue", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="mr") {
		me->set_skill("shenyuan-gong", lv);
		me->set_skill("yanling-shenfa", lv);
		me->set_skill("murong-jianfa", lv);
		me->set_skill("murong-daofa", lv);
		me->set_skill("xingyi-zhang", lv);
		me->set_skill("canhe-zhi", lv);
		me->set_skill("force", lv);
		me->set_skill("parry", lv);
		me->set_skill("dodge", lv);
		me->set_skill("medicine", 122);
		me->set_skill("finger", lv);
		me->set_skill("blade", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("douzhuan-xingyi", lv);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="mj") {
		me->set_skill("shenghuo-shengong", lv);
                me->set_skill("jiuyang-shengong", lv);
		me->set_skill("piaoyi-shenfa", lv);
		me->set_skill("shenghuo-lingfa", lv);
		me->set_skill("qishang-quan", lv);
		me->set_skill("qiankun-danuoyi", lv);
		me->set_skill("hanbing-mianzhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("cuff", lv);
		me->set_skill("parry", lv);
		me->set_skill("dagger", lv);
		me->set_skill("medicine", 122);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="dls") {
		me->set_skill("longxiang-boruo", lv);
		me->set_skill("yuxue-dunxing", lv);
		me->set_skill("xuedao-jing", lv);
		me->set_skill("dashou-yin", lv);
		me->set_skill("xiangfu-lun", lv);
		me->set_skill("huoyan-dao", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("hammer", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("blade", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("huanxi-chan", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="em") {
		me->set_skill("linji-zhuang", lv);
		me->set_skill("anying-fuxiang", lv);
		me->set_skill("huifeng-jian", lv);
		me->set_skill("sixiang-zhang", lv);
		me->set_skill("jieshou-jiushi", lv);
		me->set_skill("canhe-zhi", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("hand", lv);
		me->set_skill("sword", lv);
		me->set_skill("strike", lv);
		me->set_skill("dacheng-fofa", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="qz") {
		me->set_skill("xiantian-gong", lv);
		me->set_skill("jinyan-gong", lv);
		me->set_skill("quanzhen-jianfa", lv);
		me->set_skill("haotian-zhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("sword", lv);
		me->set_skill("medicine", 122);
		me->set_skill("parry", lv);
		me->set_skill("strike", lv);
		me->set_skill("taoism", 200);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="sld") {
		me->set_skill("dulong-dafa", lv);
		me->set_skill("youlong-shenfa", lv);
		me->set_skill("tenglong-bifa", lv);
		me->set_skill("huagu-mianzhang", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("dagger", lv);
		me->set_skill("parry", lv);
		me->set_skill("medicine", 122);
		me->set_skill("strike", lv);
		me->set_skill("poison", 200);
		me->set_skill("canglang-goufa",lv);
		me->set_skill("hook",lv);
		me->start_busy(1);
		return 1;
	}
	else if ( arg =="tls") {
		me->set_skill("kurong-changong", lv);
		me->set_skill("tianlong-xiang", lv);
		me->set_skill("yiyang-zhi", lv);
		me->set_skill("duanjia-jianfa", lv);
		me->set_skill("force", lv);
		me->set_skill("dodge", lv);
		me->set_skill("finger", lv);
		me->set_skill("medicine", 122);
		me->set_skill("parry", lv);
		me->set_skill("sword", lv);
		me->set_skill("buddhism", 200);
		me->start_busy(1);
		return 1;
	}
}
*/