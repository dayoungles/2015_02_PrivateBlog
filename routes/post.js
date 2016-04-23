/**
 * Created by dayoungle on 15. 9. 21..
 */
var express = require('express');
var router = express.Router();
var mongoose = require('mongoose');
var model = require('../model/models.js');
var path = require('path');
var sess;

var url = 'mongodb://localhost:27017/pb';


router.get('/show/:id', function(req, res){
    sess = req.session;
    console.log(sess.user);
    var postId = req.params.id;
    //var userLevel = req.session.user ? req.session.user.auth: "3";

    model.posts.findOne({'_id':postId}, function (err, data) {
        model.comments.find({post:postId}, function(err, comments){
            res.render('showPost', { post: data, userName:sess.user.name, comments:comments});
        });



    });

    //model.posts
    //    .findOne({ '_id':postId})
    //    .populate('comment') // <--
    //    .exec(function (err, post) {
    //        if (err) return handlerError(err);
    //        var accessLevel = post.accessLevel;
    //        if(accessLevel < userLevel){
    //            res.redirect("/users/authFail");
    //            return;
    //        }
    //        var trimComment=[];
    //        var comment = post.comment;
    //        for(var i = 0; i< post.comment.length; i++){
    //            if(!post.comment[i].parent) {
    //                trimComment[length+1] = post.comment[i];
    //            } else {
    //                for(var j = 0; j<post.comment.length; j++){
    //
    //                    if(trimComment[j]._id != post.comment[i].parent) continue;
    //
    //                    trimComment[j].comment.comment = post.comment[i];
    //                }
    //            }
    //        }
    //        res.render('showPost', { title: 'Express', post: post, userName:sess.user.name, comments:trimComment});
    //
    //    });
    //

});




//write form page
router.get('/write', function(req, res){
    res.sendFile(path.join(__dirname + '/../public/write.html'));
});

//input post to DB
router.post('/send', function(req, res){
    req.body.date = new Date().toISOString();
    req.body.user = req.cookies.user;
    console.log('req body: '+req.body);

    var arrTag = splitTag(req.body.tag);
    req.body.tag = arrTag;


    var post = new model.posts(req.body);

    post.save(function (err, data) {
        if (err) return handleError(err);
        res.redirect('/index/1');
    });
});

var splitTag = function(tagString){
    var list;

    if(tagString.indexOf(",") == -1){
        list = [];
        return list;
    }

    list = tagString.split(",");
    for(var i = 0; i< list.length; i++){
        list[i]= list[i].replace("#", "");
    }
    console.log("tag parsed: " + list);
    return list;
};

router.get('/searchResult/:tag', function(req, res){
    //TODO
    // db post collection의 tag에서 주어진 req.body.tag를 검색한다.
    // 결과로 나온 post의 title과 작성자를 data에 붙여서 돌려보내준다.
    // 결과가 없으면 noresult를 data에 붙여서 보내도 괜춘할 듯.
    var tag= req.params.tag;
    model.posts.find({tag:tag}, function(err, data){
        res.render('searchResult', { title: 'Express', res: data});
    });
});



router.post('/addComment', function(req, res){
    //TODO
    //db comments 에 댓글 단 사람, 댓글이 달린 postId, 댓글 내용을 입력한다.
    req.body.date= new Date().toISOString();
    var newComment = new model.comments(req.body);
    var postId = req.body.post;
    newComment.save(function(err, data){
        res.redirect("/post/show/"+postId);
    });
});

router.get('/deletePost/:postId', function(req, res){
    //TODO
    // 세션을 가지고 와서 삭제요청을 한 사용자의 id를 확인한다.
    // postid를 이용해서 해당 포스트의 작성자가 요청한 사용자와 같은지 확인한다.
    //같으면     // postId를 찾아서 db posts에서 삭제한다
    //같지 않으면 권한이 없음을 알려주고 원래 페이지로 내버려둔다.
    //index페이지로
});





router.get('/deleteComment/:postId', function(req, res){
    //req.body.commentId를 해서 commentId를 확보해놓는다.
    //삭제를 요청한 사용자의 id를 확인해 놓는다.
    //그 comment의 작성자와 삭제를 요청한
});
/*
 router.post('/comment/:id', function (req, res) {
 mongoose.connect(url, function (err) {
 if (err) {console.log(err)};
 // content: String,
 // author: String,
 // postedAt: { type: Date, default: Date.now },
 // post_id: Schema.Types.ObjectId

 console.log(req.cookies);
 if(req.cookies.user){
 model.user.findOne({
 _id: req.cookies.user
 }, function (err, data) {
 req.body.author = data.fullname;
 req.body.postedAt = new Date().toISOString();
 req.body.post_id = req.params.id;

 var comment = new model.comment(req.body);

 comment.save(function (err, data) {
 if (err) {console.log("Danger user err :"+err)};
 // res.json(data);
 res.redirect('/post/'+req.params.id);

 mongoose.disconnect();
 })
 })
 }
 });
 })
 */


module.exports = router;