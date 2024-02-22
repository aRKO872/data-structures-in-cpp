struct TreeNode {
    string name;
    int lockedBy;
    int lockedCount;
    vector<TreeNode*> childs;
    TreeNode* parent;
    set<TreeNode*> lockedDescendents;
};

bool lock(string name, int id) {
    TreeNode* r = nameToTreeNodeMapping[name];

    // Check if the node or its descendants are already locked
    if (r->lockedCount > 0 || r->lockedDescendents.size() > 0)
        return false;

    // Lock the current node
    r->lockedCount++;

    // If the node is already locked by someone else, release the lock and return false
    if (r->lockedCount > 1) {
        r->lockedCount--;
        return false;
    }

    // Check and lock ancestors
    TreeNode* par = r->parent;
    while (par) {
        if (par->lockedCount > 0 || r->lockedDescendents.size() > 0) {
            // Release the lock on the current node and its descendants
            r->lockedCount--;
            TreeNode* par1 = r->parent;
            while (par1 != par) {
                par1->lockedDescendents.erase(r);
                par1 = par1->parent;
            }
            return false;
        }

        // Lock the ancestor
        par->lockedDescendents.insert(r);
        par = par->parent;
    }

    // Set the lock information for the current node
    r->lockedBy = id;
    return true;
}
