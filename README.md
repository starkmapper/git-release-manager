# git-release-manager
Ease the management of you release and hotfix branches

Goals
-----------------
git release manager(GRM) is a wrapper around git and git-flow helping you with version numbering.
GRM allows you to auto increment version numbers and, providing branch naming is consistent, use git flow with maintenance versions/branches.

Wat does it do?
--------------------
- uuhhm... nothing yet..

Wat it will do?
------------------
- Auto-increment verson numbers for you
- Prevent typos in release/hotfix branch names
- Help git-flow manage maintenance branches properly
- Make your life easy
- turn git-flow into a plumbing command

Wat won't it do
------------------------
- write code
- fix your computer
- make coffee
- fetch lunch

Semantics
------------
Git commands will be single level (unlike git flow with its 500 command level madness).

Calling semantics will be like git branch and git tag commands, listing existing items when called without arguments, and creating  new ones with optional origin.

Examples:
Listing items:

    $ git hotfix
    1.2.3.1
    1.1.5.21
    1.1.4.13
    1.0.4
    0.7
    $ git release
    1.2.3
    1.1.5
    1.1.4
    1.0
    0

Starting a new item:

    $ git hotfix 1.2.3
    Creating new hotfix 1.2.3.2
    $ git release 1.2
    Creating new release 1.2.3.0

Implementation considerations
---------------------------
- A wizard (possibly with gui) will be provided to ease version selecting. Hopefully I will be able to provide bash completion as well.
- Version number formats, separators and prefixes will be read from existing tags/branches. Anything around the version number will be purged, separators will be preserved. Git flow should handle prefixes. Suffixes should be suffocated.
- Prefixes could, at some point, be read from (git flow) config, but that would be a less generic approach, and slow things down. 
- Regular git and git flow commands will be used to do the actual git work. This could be replaced with libgit later on, if performance becomes an issue.

Possible future features (not necessarily in the scope of this project)
---------------------
- Testing/beta/RC/stable release staging branch handling could be added, but I don't care for it. Could be a separate tool though.

Why the hell are you branching the crap out of this repo?
--------------------------------------------------
To be able to use it as a test repo for this tool
It will get worse... Much, much worse...


Implemented
---------------------
- Version objects with:
  - proper conversion/construction semantics
    - (vector of) integers
    - randomly formatted version string with any prefix or annotation

To implement
---------------------

- Version objects with:
  - means for natural sorting (i.e. 1.2 < 1.2.1 and 1.20 > 1.2.1)
    - Convert version to one big int for easy sorting OR provide custom sorting semantics (comparison operators)
- read version tags/branches 
- call git-flow appropriately
- detect unfinished releases/hotfixes
- bring in Gandalf
- do something with bash completion

