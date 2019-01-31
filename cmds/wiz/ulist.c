// user list by renlai 添加查看quest功能

inherit F_CLEAN_UP;

int main(string str)
{
        object *ob,temp;
        int i;
		string vip="普通用户";
		string jiebai="结拜未开";	
        int print=0;		

		
	string a="张三李四王五";
	string b="李六";
	int ret=0;
	
	ret=strsrch(a,b);
	write("***"+ret+"***\n");
	ob = filter_array(objects(), (: userp :));
	for(i=0; i<sizeof(ob); i++)
	{	    	temp=ob[i];
	    if (temp->query("m-card-vip")) vip="月卡";
		else if (temp->query("y-card-vip")) vip="年卡";
		else if (temp->query("buyvip")) vip="终身";
		if (temp->query("quest/jiebai/pass")) { 
		jiebai="*解开结拜*"; 
		print=1;
		}
		if (temp->query("double_attack")) jiebai="*解开互搏*";
        if (print==1) write(sprintf("%10s : %40O%s\n", temp->query("id"),vip,jiebai,temp,
		interactive(temp)?"":" 断线中，"));
		vip="普通用户";
		jiebai="结拜未开";
		print=0;
	}
        return 1;
	
}

int help(object me)
{
write(@HELP
指令格式 : ulist

将线上所有玩家的/obj/user number 显示出来。
HELP
    );
    return 1;
}
