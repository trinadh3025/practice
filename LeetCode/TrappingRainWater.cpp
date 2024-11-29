#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution{
public:
	int trap(vector<int>& height) {
		if(height.empty()) return 0;
		int result = 0;
		int l=0, r=height.size()-1;
		int leftMax = height[l], rightMax = height[r];
		//two pointer approach
		//where we traverse based the left and right indexes heights.
		//we move l(i.e left index) and r(i.e right index) based on 
		//the minimum of the leftMax and rightMax. sub sequently add
		//them to result
		//water could be stored at particular index i is
		// min_height(i-1, i+) - height[i]
		while (l < r){
			if(leftMax < rightMax){
				l++;
				leftMax = max(leftMax, height[l]);
				result = result + leftMax - height[l];
			}else{
				r--;
				rightMax = max(rightMax, height[r]);
				result = result + rightMax - height[r];
			}
		}
		
		
		return result;
	}
};
int main(){
	Solution s;
	vector<int> heights = {0,2,0,3,1,0,1,3,2,1};   
	cout << s.trap(heights)<< endl;
	return 0;
}
