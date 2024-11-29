#include<iostream>
#include<vector>

using namespace std;

class Solution{
public:
	int maxProfit(vector<int>& prices){
		if(prices.empty()) return 0;
		int profit = 0;
		int l=0, r = prices.size()-1;

		while(l<r){
			int temp = prices[l] - prices[r];
			if(temp>profit){
				profit = temp;
			}
			if(prices[l] > prices[l+1])
				l++;
			if(prices[r] < prices[r-1])
				r--;
		}
		return profit;
	}
	int maxProfit_o(vector<int>& prices) {
		int l=0, r = 1;
		int profit = 0;
		while(r<prices.size()){
		    if(prices[l]<prices[r]){
			int temp = prices[r]-prices[l];
			if(temp > profit)
			    profit = temp;
		    }
		    else{
			l=r;
		    }
		    r++;
		}
		return profit;
    	}
};

int main(){
	Solution s;
	vector<int> priceList = {7,1,5,3,6,4};

	cout << "Max profit: " << s.maxProfit_o(priceList) << endl;

	return 0;
}
