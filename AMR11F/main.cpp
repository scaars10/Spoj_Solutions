#include<stdio.h>
#include<malloc.h>
typedef struct node
{
	long long int dest,cost;
	struct node *next;
}node;


node *head[301];
long long int tower[101][101][2];	//stores nodes of each tower with their indices in sparse table
long long int toptower[101];		//stores number of nodes in each tower
long long int dist[301][301];		//stores distances between nodes
long long int path[301][301];		//stores path for tracing
long long int max=10000000000;

long long int add_node(long long int source,long long dest,long long int cost);

long long int receive(long long int source,long long int dest);

void swap(long long int *a,long long int *b)
{
	long long int x=*a;
	x=*a;
	*a=*b;
	*b=x;
	return;
}

long long int min(long long int a,long long int b)
{
	if(a>b)
		return b;
	return a;
}
void bin_search(long long int tow,long long int floor,long long int *a,long long int *b);
main()
{
	long long int t,n,m,floor,q,i,nodes,j,k,tow1,flr1,tow2,flr2,cst,temp1,temp2,x,y,z,pos1,pos2,a,b,c,d,e;
	scanf("%lld",&t);
	while(t--)
	{
		scanf("%lld",&n);
		scanf("%lld",&floor);
		scanf("%lld",&m);

		for(i=0;i<=300;i++)
		{
			head[i]=(node*)malloc(sizeof(node));
			head[i]->next=0;
		}

		nodes=n;
		for(i=0;i<n;i++)
		{
			toptower[i]=0;
			tower[i][0][0]=0;
			tower[i][0][1]=i;
			add_node(i,(i+1)%n,1);
			add_node((i+1)%n,i,1);
		}
		for(i=0;i<m;i++)
		{
			scanf("%lld",&tow1);
			scanf("%lld",&flr1);
			scanf("%lld",&tow2);
			scanf("%lld",&flr2);
			scanf("%lld",&cst);
			flr1--,tow1--,flr2--,tow2--;
			for(j=0;j<=toptower[tow1];j++)
			{
				if(tower[tow1][j][0]==flr1)
					break;
			}
			pos1=j;
			if(j==toptower[tow1]+1)
			{
				toptower[tow1]++;
				tower[tow1][j][0]=flr1;
				temp1=nodes;
				tower[tow1][j][1]=temp1;
				nodes++;
			}
			else
			{
				temp1=tower[tow2][j][1];
			}
			for(j=0;j<=toptower[tow2];j++)
			{
				if(tower[tow2][j][0]==flr2)
					break;
			}
			pos2=j;
			if(j==toptower[tow2]+1)
			{
				toptower[tow2]++;
				tower[tow2][j][0]=flr2;
				temp2=nodes;
				tower[tow2][j][1]=temp2;
				nodes++;
			}

			else
			{
				temp2=tower[tow2][j][1];
			}
			//printf("temp1 is %lld temp2 is %lld\n",temp1,temp2);
			add_node(temp1,temp2,cst);
			add_node(temp2,temp1,cst);

			for(j=0;j<=toptower[tow1];j++)
			{

				if(j==pos1)
					continue;

				x=tower[tow1][j][0]-tower[tow1][pos1][0];

				if(x<0)
					x=-x;

				add_node(tower[tow1][j][1],tower[tow1][pos1][1],x);
				add_node(tower[tow1][pos1][1],tower[tow1][j][1],x);
			}
			for(j=0;j<=toptower[tow2];j++)
			{

				if(j==pos2)
					continue;

				x=tower[tow2][j][0]-tower[tow2][pos2][0];

				if(x<0)
					x=-x;

				add_node(tower[tow2][j][1],tower[tow2][pos2][1],x);
				add_node(tower[tow2][pos2][1],tower[tow2][j][1],x);
			}
		}
		for(i=0;i<nodes;i++)
		{
			for(j=0;j<nodes;j++)
			{
				if(i==j)
				{
					dist[i][j]=0;
					path[i][j]=i;
					continue;
				}
				x=receive(i,j);
				if(x==max)
				{
					dist[i][j]=max;
					path[i][j]=nodes;
					continue;
				}
				dist[i][j]=x;
				path[i][j]=i;
			}
		}
		for(k=0;k<nodes;k++)
		{
			for(i=0;i<nodes;i++)
			{
				for(j=0;j<nodes;j++)
				{
					if(dist[i][j]>dist[i][k]+dist[k][j])
					{
						dist[i][j]=dist[i][k]+dist[k][j];
						path[i][j]=path[k][j];
					}
				}
			}
		}
		/*for(i=0;i<nodes;i++)
		{
			for(j=0;j<nodes;j++)
			{
				printf("distance between node %lld and node %lld is %lld\n",i,j,dist[i][j]);
			}
		}*/

		for(i=0;i<n;i++)
		{
			for(j=0;j<=toptower[i];j++)
			{
				for(k=j;k>0;k--)
				{
					if(tower[i][k][0]<tower[i][k-1][0])
					{
						swap(&tower[i][k][0],&tower[i][k-1][0]);
						swap(&tower[i][k][1],&tower[i][k-1][1]);
					}
					else
						break;
				}
			}
		}
		scanf("%lld",&q);
	/*	for(i=0;i<n;i++)
		{
			printf("In tower %lld these are nodes\n",i);
			for(j=0;j<=toptower[i];j++)
				printf("%lld\n",tower[i][j][0]);
		}*/
		while(q--)
		{
			scanf("%lld",&tow1);
			scanf("%lld",&flr1);
			scanf("%lld",&tow2);
			scanf("%lld",&flr2);
			tow1--,flr1--,tow2--,flr2--;
			if(tow1==tow2)
			{
				e=flr2-flr1;
				if(e<0)
					e=-e;
			}
			else
			{
				e=flr1+flr2;
				if(tow1>tow2)
				{
					temp2=tow1;
					temp1=tow2;
				}
				else
				{
					temp2=tow2;
					temp1=tow1;
				}
				x=min(temp2-temp1,temp1+n-temp2);
				e=e+x;
			}
			//printf("e is %lld\n",e);
			bin_search(tow1,flr1,&a,&b);
			//printf("lower floor than %lld in %lld is %lld higher is %lld\n",flr1,tow1,tower[tow1][a][0],tower[tow1][b][0]);
			bin_search(tow2,flr2,&c,&d);
			//printf("lower floor than %lld in %lld is %lld higher is %lld\n",flr2,tow2,tower[tow2][c][0],tower[tow2][d][0]);
			x=tower[tow2][c][0]-flr2;		//tower[tow2][flr2][0];
			if(x<0)
				x=-x;

			y=tower[tow2][d][0]-flr2;			//tower[tow2][flr2][0];
			if(y<0)
				y=-y;


			temp1=dist[tower[tow1][a][1]][tower[tow2][c][1]];
			temp1 += x;


			z=tower[tow1][a][0]-flr1;		//tower[tow1][flr1][0];
			if(z<0)
				z=-z;

			temp2=dist[tower[tow1][a][1]][tower[tow2][d][1]];
			temp2=temp2+y;

			a=min(temp1,temp2);
			a=a+z;

			temp1=dist[tower[tow1][b][1]][tower[tow2][c][1]];
			temp2=dist[tower[tow1][b][1]][tower[tow2][d][1]];
			temp1=temp1+x;
			temp2=temp2+y;

			z=tower[tow1][b][0]-flr1;		//tower[tow1][flr1][0];
			if(z<0)
				z=-z;
			b=min(temp1,temp2);
			b=b+z;

			temp1=min(a,b);

			temp1=min(temp1,e);
			printf("%lld\n",temp1);
		}
	}
}

void bin_search(long long int tow,long long int flr,long long int *a,long long int *b)
{
	long long int low=0,high=toptower[tow],mid=(high+low)/2,i;
	for(i=low;i<=high;i++)
	{
		if(tower[tow][i][0]>flr)
			break;
	}
	if(i==high+1)
	{
		*b=high;
		*a=high-1;
		if(*a<0)
			*a=0;
		return;
	}
	*b=i;
	*a=i-1;
	return;
	/*while(high>low)
	{
		mid=(high+low)/2;
		printf("low is %lld high is %lld\n",low,high);
		if(tower[tow][mid][0]==flr)
		{
			break;
		}
		if(tower[tow][low][0]==flr)
		{
			mid=low;
			break;
		}
		if(tower[tow][high][0]==flr)
		{
			mid=high;
			break;
		}
		if((tower[tow][mid][0]>flr)&&(tower[tow][mid+1][0]>flr))
		{
			high=mid;
		}
		else if((tower[tow][mid][0]<flr)&&(tower[tow][mid+1][0]<flr))
		{
			low=mid+1;
		}
		else
		{
			break;
		}
	}
	if(mid==0)
	{
		(*a)=0,(*b)=min(toptower[tow],1);
		return;
	}
	if(mid==toptower[tow]);
	{
		(*b)=mid;
		(*a)=mid-1;
		return;
	}
	if(tower[tow][mid][0]>=flr)
	{
		(*b)=mid;
		(*a)=mid-1;;
	}
	else
	{
		(*a)=mid;
		(*b)=mid+1;
	}
	return;*/
}


long long int receive(long long int source,long long int dest)
{
	node *x=head[source]->next;
	while(x)
	{
		if(x->dest==dest)
			return x->cost;
		x=x->next;
	}
	return max;
}


long long int add_node(long long int source,long long int dest,long long int cost)
{
	node *x=head[source]->next,*y=head[source];
	//printf("Source is %lld\n",source);
	while(x)
	{
		if(x->dest==dest)
		{
			if(x->cost<cost)
				return 1;
			x->cost=cost;
				return 1;
		}
		y=x;
		x=x->next;
	}
	x=(node*)malloc(sizeof(node));
	x->cost=cost;
	x->dest=dest;
	y->next=x;
	x->next=0;
	return 0;
}
