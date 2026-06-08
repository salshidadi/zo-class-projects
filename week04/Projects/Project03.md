# Social Media Data Structure

A C program that models a social media network as a directed graph where each user node tracks followers and followings.

# Overview

The program creates a network of users where each user can follow and unfollow others. Every user node independently tracks who follows them and who they follow, and the program can display that information for any user in the network.

# Concept

The project focuses on:

- Directed graph design in C
- Managing directional relationships between nodes
- Dynamic memory management
- Traversing and querying a connected network

A relationship between two users is directional — following someone does not mean they follow back. Each user node maintains two independent lists: one for followers and one for followings. Every follow or unfollow action updates both sides of the relationship accordingly.

# How It Works

1. A set of user nodes is created and added to the network
2. Users can follow or unfollow each other
3. Each follow action updates both the follower's followings list and the followed user's followers list
4. The program can print any user's information showing their following count, followings, follower count, and followers

# Example

## Output
```text
----- user-1 -----

following 2 users: user-2 user-5

has 0 followers:


--- user-1 unfollowed user-2 ----

----- user-1 -----

following 1 users: user-5

has 0 followers:
```
